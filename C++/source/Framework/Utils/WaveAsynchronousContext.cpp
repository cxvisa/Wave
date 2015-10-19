/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

WaveAsynchronousContext::WaveAsynchronousContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : m_pCaller (pCaller),
      m_pCallback (pCallback),
      m_pCallerContext (pCallerContext)
{
    m_completionStatus = WAVE_MESSAGE_ERROR;
}

WaveAsynchronousContext::WaveAsynchronousContext (const WaveAsynchronousContext &prismAsynchronousContext)
    : m_pCaller (NULL),
      m_pCallback (NULL),
      m_pCallerContext (NULL)
{
    trace (TRACE_LEVEL_FATAL, "WaveAsynchronousContext::WaveAsynchronousContext : Copy constructing WaveAsynchronousContext does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);
}

WaveAsynchronousContext::~WaveAsynchronousContext ()
{
    garbageCollect ();
}

WaveAsynchronousContext &WaveAsynchronousContext::operator = (const WaveAsynchronousContext &prismAsynchronousContext)
{
    trace (TRACE_LEVEL_FATAL, "WaveAsynchronousContext::operator = : Assigning to a WaveAsynchronousContext does not make sense and hence not allowed.");
    waveAssert (false, __FILE__, __LINE__);

    return (*this);
}

void WaveAsynchronousContext::setCompletionStatus (const ResourceId &status)
{
    m_completionStatus = status;
}

ResourceId WaveAsynchronousContext::getCompletionStatus ()
{
    return (m_completionStatus);
}

void *WaveAsynchronousContext::getPCallerContext ()
{
    return (m_pCallerContext);
}

void WaveAsynchronousContext::callback ()
{
    if ((NULL != m_pCaller) && (((WaveAsynchronousCallback) NULL) != m_pCallback))
    {
        (m_pCaller->*m_pCallback) (this);
    }
}

void WaveAsynchronousContext::addManagedObjectsForGarbageCollection (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection)
{
    m_managedObjectsForGarbageCollection.insert (m_managedObjectsForGarbageCollection.end (), managedObjectsForGarbageCollection.begin (), managedObjectsForGarbageCollection.end ());
}

void WaveAsynchronousContext::addManagedObjectForGarbageCollection (WaveManagedObject *pWaveManagedObjectForGarbageCollection)
{
    waveAssert (NULL != pWaveManagedObjectForGarbageCollection, __FILE__, __LINE__);

    m_managedObjectsForGarbageCollection.push_back (pWaveManagedObjectForGarbageCollection);
}

void WaveAsynchronousContext::garbageCollect ()
{
    UI32 numberOfManagedObjectsForGarbageCollection = m_managedObjectsForGarbageCollection.size ();
    UI32 i                                          = 0;

    for (i = 0; i < numberOfManagedObjectsForGarbageCollection; i++)
    {
        waveAssert (NULL != m_managedObjectsForGarbageCollection[i], __FILE__, __LINE__);

        delete (m_managedObjectsForGarbageCollection[i]);

        m_managedObjectsForGarbageCollection[i] = NULL;
    }

    m_managedObjectsForGarbageCollection.clear ();
}

}
