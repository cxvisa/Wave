/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include <map>

namespace WaveNs
{

static map<PrismServiceId, PrismServiceId> s_localPrismServices;

WaveLocalObjectManager::WaveLocalObjectManager (const string &objectManagerName, const UI32 &stackSize, const vector<UI32> *pCpuAffinityVector)
    : WaveObjectManager (objectManagerName, stackSize, pCpuAffinityVector)
{
    s_localPrismServices[getServiceId ()] = getServiceId ();
}

WaveLocalObjectManager::~WaveLocalObjectManager ()
{
}

bool WaveLocalObjectManager::isALocalPrismService ()
{
    return (true);
}

bool WaveLocalObjectManager::isALocalService (const PrismServiceId &prismServiceId)
{
    map<PrismServiceId, PrismServiceId>::iterator element = s_localPrismServices.find (prismServiceId);
    map<PrismServiceId, PrismServiceId>::iterator end     = s_localPrismServices.end ();

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
