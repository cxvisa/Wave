/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include <map>

namespace WaveNs
{

static map<WaveServiceId, WaveServiceId> s_localWaveServices;

WaveLocalObjectManager::WaveLocalObjectManager (const string &objectManagerName, const UI32 &stackSize, const vector<UI32> *pCpuAffinityVector)
    : WaveObjectManager (objectManagerName, stackSize, pCpuAffinityVector)
{
    s_localWaveServices[getServiceId ()] = getServiceId ();
}

WaveLocalObjectManager::~WaveLocalObjectManager ()
{
}

bool WaveLocalObjectManager::isALocalWaveService ()
{
    return (true);
}

bool WaveLocalObjectManager::isALocalService (const WaveServiceId &waveServiceId)
{
    map<WaveServiceId, WaveServiceId>::iterator element = s_localWaveServices.find (waveServiceId);
    map<WaveServiceId, WaveServiceId>::iterator end     = s_localWaveServices.end ();

    if (element == end)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
