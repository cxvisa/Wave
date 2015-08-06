/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef OBJECTTRACKER_H
#define OBJECTTRACKER_H

#include "Framework/Types/Types.h"
#include "Framework/MultiThreading/PrismPosixThread.h"
#include "Framework/Utils/PrismMutex.h"

#include <map>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveManagedObject;
class WaveObjectManager;

class ObjectTracker
{
    private :
        static bool isAKnownMessage (const WaveManagedObject *pWaveManagedObject);
        static bool isAKnownManagedObjectWithBt (const WaveManagedObject *pWaveManagedObject);
        static void clearCurrentlyAllocatedObjectsWithBt ();

    protected :
    public :
        static void addToObjectTracker           (const WaveManagedObject *pWaveManagedObject, const bool &queryResults = false, WaveObjectManager *pWaveObjectManager = NULL);
        static void deleteFromObjectTracker      (const WaveManagedObject *pWaveManagedObject);
        static void getObjects                   (const WaveServiceId &prismServiceId, vector<string> &objectClassNames, vector<string> &objectNames, vector<bool> &queryResults, vector<string> &btStrings);

        static void addQueriedObjectsToBtTracker (vector<WaveManagedObject *> *queryResults);
        static void changeBtTrackerState         (const bool &btTrackerState);

    // Now the data members

    private :
        static map<WaveThreadId, map<const WaveManagedObject *, const WaveManagedObject *> > m_currentlyAllocatedObjectsByThread;
        static map<const WaveManagedObject *, WaveThreadId>                                  m_currentlyAllocatedObjects;
        static map<const WaveManagedObject *, bool>                                           m_currentlyAllocatedObjectsForQueyResults;

        static bool                                                                           m_trackingObjectsWithBt;
        static map<const WaveManagedObject *, string>                                         m_currentlyAllocatedObjectsWithBt;

        static PrismMutex                                                                     m_objectTrackerMutex;

    protected :
    public :
};

}

#endif // OBJECTTRACKER_H
