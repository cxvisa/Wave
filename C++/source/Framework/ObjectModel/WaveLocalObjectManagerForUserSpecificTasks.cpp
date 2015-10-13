/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/Utils/WaveMutex.h"
#include <map>

namespace WaveNs
{

map<WaveServiceId, WaveServiceId> s_userSpecificServicesMap;
WaveMutex s_userSpecificServicesMapMutex;

WaveLocalObjectManagerForUserSpecificTasks::WaveLocalObjectManagerForUserSpecificTasks (const string &objectManagerName, const UI32 &stackSize, const vector<UI32> *pCpuAffinityVector)
    : WaveLocalObjectManager (objectManagerName, stackSize, pCpuAffinityVector)
{
    addToUserspecificServicesMap (getServiceId ());
}

WaveLocalObjectManagerForUserSpecificTasks::~WaveLocalObjectManagerForUserSpecificTasks ()
{
}

void WaveLocalObjectManagerForUserSpecificTasks::addToUserspecificServicesMap (const WaveServiceId &waveServiceId)
{
    s_userSpecificServicesMapMutex.lock ();
    s_userSpecificServicesMap[waveServiceId] = waveServiceId;
    s_userSpecificServicesMapMutex.unlock ();
}

bool WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (const WaveServiceId &waveServiceId)
{
    s_userSpecificServicesMapMutex.lock ();

    map<WaveServiceId, WaveServiceId>::iterator element = s_userSpecificServicesMap.find (waveServiceId);
    map<WaveServiceId, WaveServiceId>::iterator end     = s_userSpecificServicesMap.end ();
    bool                                          found   = false;

    if (element != end)
    {
        found = true;
    }
    else
    {
        found = false;
    }

    s_userSpecificServicesMapMutex.unlock ();

    return (found);
}

}
