/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/ObjectTracker/ObjectTracker.h"
#include <Framework/MultiThreading/WaveThread.h>
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

map<WaveThreadId, map<const WaveManagedObject *, const WaveManagedObject *> > ObjectTracker::m_currentlyAllocatedObjectsByThread;
map<const WaveManagedObject *,WaveThreadId>                                   ObjectTracker::m_currentlyAllocatedObjects;
map<const WaveManagedObject *, bool>                                           ObjectTracker::m_currentlyAllocatedObjectsForQueyResults;
bool                                                                           ObjectTracker::m_trackingObjectsWithBt = false;
map<const WaveManagedObject *, string>                                         ObjectTracker::m_currentlyAllocatedObjectsWithBt;
WaveMutex                                                                     ObjectTracker::m_objectTrackerMutex;

bool ObjectTracker::isAKnownMessage (const WaveManagedObject *pWaveManagedObject)
{
    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

    map<const WaveManagedObject *, WaveThreadId>::iterator element    = m_currentlyAllocatedObjects.find (pWaveManagedObject);
    map<const WaveManagedObject *, WaveThreadId>::iterator endElement = m_currentlyAllocatedObjects.end ();
    bool                                               found      = false;

    if (endElement != element)
    {
        found = true;
    }

    return (found);
}

void ObjectTracker::addToObjectTracker(const WaveManagedObject *pWaveManagedObject, const bool &queryResults, WaveObjectManager *pWaveObjectManager)
{
    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

    m_objectTrackerMutex.lock ();

    if (true == (isAKnownMessage (pWaveManagedObject)))
    {
        trace (TRACE_LEVEL_FATAL, "ObjectTracker::addToObjectTracker : Duplicate Tracking of a ManagedObject detected.");
        waveAssert (false, __FILE__, __LINE__);

        m_objectTrackerMutex.unlock ();

        return;
    }

    if (true == ObjectTracker::m_trackingObjectsWithBt)
    {
        if (true == (isAKnownManagedObjectWithBt (pWaveManagedObject)))
        {
            // When bt tracker is turned off, we clear "MO pointer" --> "bt string" map too.
            trace (TRACE_LEVEL_FATAL, "ObjectTracker::addToObjectTracker : Duplicate Tracking of a ManagedObject with Bt detected.");
            waveAssert (false, __FILE__, __LINE__);

            m_objectTrackerMutex.unlock ();

            return;
        }
    }

    WaveThreadId thisThread;

    if (true == queryResults)
    {
        thisThread = (WaveThread::getWaveThreadForServiceId (pWaveObjectManager->getServiceId ()))->getId ();
    }
    else
    {
        thisThread = WaveThread::getSelf ();
    }

    m_currentlyAllocatedObjectsByThread[thisThread][pWaveManagedObject] = pWaveManagedObject;
    m_currentlyAllocatedObjects[pWaveManagedObject]                     = thisThread;
    m_currentlyAllocatedObjectsForQueyResults[pWaveManagedObject]       = queryResults;

    if (true == ObjectTracker::m_trackingObjectsWithBt)
    {
        // If these objects are from db query, then they are handled separately in query routines of object managers.
        if (false == queryResults)
        {
            string btstring;
            FrameworkToolKit::obtainBtString (2,10, btstring);
            m_currentlyAllocatedObjectsWithBt[pWaveManagedObject]           = btstring;
        }
    }
    m_objectTrackerMutex.unlock ();
}

void ObjectTracker::deleteFromObjectTracker(const WaveManagedObject* pWaveManagedObject)
{
    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

    m_objectTrackerMutex.lock ();

    if (false == (isAKnownMessage (pWaveManagedObject)))
    {
        trace (TRACE_LEVEL_FATAL, "ObjectTracker::deleteFromObjectTracker :Deleting of an unknown ManagedObject. Possible DOUBLE DELETION / MEMORY CORRUPTION Detected.");
        waveAssert (false, __FILE__, __LINE__);

        m_objectTrackerMutex.unlock ();

        return;
    }

    if (true == ObjectTracker::m_trackingObjectsWithBt)
    {
        if (true == (isAKnownManagedObjectWithBt (pWaveManagedObject)))
        {
            m_currentlyAllocatedObjectsWithBt.erase (pWaveManagedObject);
        }
    }

    m_currentlyAllocatedObjectsByThread[m_currentlyAllocatedObjects[pWaveManagedObject]].erase (pWaveManagedObject);
    m_currentlyAllocatedObjects.erase (pWaveManagedObject);
    m_currentlyAllocatedObjectsForQueyResults.erase (pWaveManagedObject);

    m_objectTrackerMutex.unlock ();
}

void ObjectTracker::getObjects (const WaveServiceId &waveServiceId, vector<string> &objectClassNames, vector<string> &objectNames, vector<bool> &queryResults, vector<string> &btStrings)
{
    m_objectTrackerMutex.lock ();

    WaveThread *pWaveThread = WaveThread::getWaveThreadForServiceId (waveServiceId);

    if (NULL == pWaveThread)
    {
        tracePrintf (TRACE_LEVEL_ERROR, true, false, "ObjectTracker::getMessages : Could not find a Wave Thread that corresponds to Wave Service ID : %u", waveServiceId);

        m_objectTrackerMutex.unlock ();
        return;
    }

    WaveThreadId                                                                            waveThreadId    = (WaveThread::getWaveThreadForServiceId (waveServiceId))->getId ();
    map<WaveThreadId, map<const WaveManagedObject *, const WaveManagedObject *> >::iterator threadElement    = m_currentlyAllocatedObjectsByThread.find (waveThreadId);
    map<WaveThreadId, map<const WaveManagedObject *, const WaveManagedObject *> >::iterator threadEndElement = m_currentlyAllocatedObjectsByThread.end  ();

    string btstring = "";
    if (threadEndElement != threadElement)
    {
        map<const WaveManagedObject *, const WaveManagedObject *>::iterator messageElement    = m_currentlyAllocatedObjectsByThread[waveThreadId].begin ();
        map<const WaveManagedObject *, const WaveManagedObject *>::iterator messageEndElement = m_currentlyAllocatedObjectsByThread[waveThreadId].end   ();

        while (messageEndElement != messageElement)
        {
            const WaveManagedObject *pWaveManagedObject = messageElement->second;

            waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

            objectClassNames.push_back (pWaveManagedObject->getObjectClassName ());
            objectNames.push_back (pWaveManagedObject->getName ());
            queryResults.push_back (m_currentlyAllocatedObjectsForQueyResults[pWaveManagedObject]);

            if (true == ObjectTracker::m_trackingObjectsWithBt)
            {
                if (isAKnownManagedObjectWithBt (pWaveManagedObject))
                {
                    btstring = m_currentlyAllocatedObjectsWithBt[pWaveManagedObject];
                }
                else
                {
                    btstring = "";
                }
            }
            else
            {
                btstring = "";
            }
            btStrings.push_back (btstring);

            messageElement++;
        }
    }

    m_objectTrackerMutex.unlock ();
}

bool ObjectTracker::isAKnownManagedObjectWithBt (const WaveManagedObject *pWaveManagedObject)
{
    waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

    map<const WaveManagedObject *, string>::iterator element    = m_currentlyAllocatedObjectsWithBt.find (pWaveManagedObject);
    map<const WaveManagedObject *, string>::iterator endElement = m_currentlyAllocatedObjectsWithBt.end ();
    bool                                             found      = false;

    if (endElement != element)
    {
        found = true;
    }

    return (found);
}

void ObjectTracker::addQueriedObjectsToBtTracker (vector<WaveManagedObject *> *pWaveManagedObjectVector)
{
    if (NULL == pWaveManagedObjectVector)
    {
        // results can be NULL;
        return;
    }

    m_objectTrackerMutex.lock ();

    if (false == ObjectTracker::m_trackingObjectsWithBt)
    {
        m_objectTrackerMutex.unlock ();
        return;
    }

    WaveManagedObject                       *pWaveManagedObject     = NULL;
    vector<WaveManagedObject *>::iterator   managedObjectIterator;
    string                                  btstring                = "";

    for (managedObjectIterator = pWaveManagedObjectVector->begin (); managedObjectIterator != pWaveManagedObjectVector->end(); managedObjectIterator++)
    {
        pWaveManagedObject = *managedObjectIterator;
        if (true == (isAKnownManagedObjectWithBt (pWaveManagedObject)))
        {
            trace (TRACE_LEVEL_FATAL, "ObjectTracker::addToObjectTracker : Duplicate Tracking of a ManagedObject with Bt detected.");
            waveAssert (false, __FILE__, __LINE__);

            m_objectTrackerMutex.unlock ();

            return;
        }

        FrameworkToolKit::obtainBtString (2, 10, btstring);
        m_currentlyAllocatedObjectsWithBt[pWaveManagedObject]           = btstring;
        btstring.clear ();
    }

    m_objectTrackerMutex.unlock ();
}

void ObjectTracker::changeBtTrackerState (const bool &btTrackerState)
{
    m_objectTrackerMutex.lock ();

    if (true == btTrackerState)
    {
        ObjectTracker::m_trackingObjectsWithBt = true;
        trace (TRACE_LEVEL_INFO, "ObjectTracker::changeBtTrackerState : Tracking with Bt is enabled.");
    }
    else
    {
        ObjectTracker::m_trackingObjectsWithBt = false;
        ObjectTracker::clearCurrentlyAllocatedObjectsWithBt ();
        trace (TRACE_LEVEL_INFO, "ObjectTracker::changeBtTrackerState : Disabled tracking with Bt and cleared history.");
    }

    m_objectTrackerMutex.unlock ();
}

void ObjectTracker::clearCurrentlyAllocatedObjectsWithBt ()
{
    m_currentlyAllocatedObjectsWithBt.erase (m_currentlyAllocatedObjectsWithBt.begin (), m_currentlyAllocatedObjectsWithBt.end ());
}

}
