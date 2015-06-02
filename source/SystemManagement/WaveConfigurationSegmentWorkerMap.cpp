/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                          *
 ***************************************************************************/

#include "SystemManagement/WaveConfigurationSegmentWorkerMap.h"
#include "SystemManagement/WaveConfigurationSegmentWorker.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

map<string, WaveConfigurationSegmentWorker *> WaveConfigurationSegmentWorkerMap::m_configurationSegmentWorkerMap;
PrismMutex WaveConfigurationSegmentWorkerMap::m_configurationSegmentWorkerMapMutex;
        
void WaveConfigurationSegmentWorkerMap::addConfigurationSegmentWorkerIntoMap  (const string &configurationSegmentName, WaveConfigurationSegmentWorker *pWaveConfigurationSegmentWorker)
{
    trace (TRACE_LEVEL_INFO, "WaveConfigurationSegmentWorkerMap::addConfigurationSegmentWorkerIntoMap : Entering ... ");

    if (false == isConfigurationSegmentNameInMap (configurationSegmentName))
    {
        m_configurationSegmentWorkerMapMutex.lock ();
        m_configurationSegmentWorkerMap[configurationSegmentName] = pWaveConfigurationSegmentWorker;
        m_configurationSegmentWorkerMapMutex.unlock ();
    }
}

bool WaveConfigurationSegmentWorkerMap::isConfigurationSegmentNameInMap (const string &configurationSegmentName)
{
    bool retVal = false;
    m_configurationSegmentWorkerMapMutex.lock ();

    map<string, WaveConfigurationSegmentWorker *>::iterator configSegmentWorkerMapIterator; 

    if (m_configurationSegmentWorkerMap.find (configurationSegmentName) != m_configurationSegmentWorkerMap.end ())
    {
        retVal = true;
    }
    else
    {
        retVal = false;
    }
    
    m_configurationSegmentWorkerMapMutex.unlock ();

    return (retVal);
}

}
