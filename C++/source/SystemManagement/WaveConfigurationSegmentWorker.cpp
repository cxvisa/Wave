/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/Utils/FrameworkToolKit.h"
#include "SystemManagement/WaveConfigurationSegmentWorker.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveConfigurationSegmentWorkerMap.h"

namespace WaveNs
{

WaveConfigurationSegmentWorker::WaveConfigurationSegmentWorker (WaveObjectManager *pWaveObjectManager, const string &configurationSegmentName, const bool isConfigExistValidationRequired)
    :   WaveWorker                  (WaveSystemManagementObjectManager::getInstance ()),
        m_configurationSegmentName      (configurationSegmentName),
        m_isConfigExistValidationRequired    (isConfigExistValidationRequired)
{
    WaveConfigurationSegmentWorkerMap::addConfigurationSegmentWorkerIntoMap (m_configurationSegmentName, this);
}        

WaveConfigurationSegmentWorker::~WaveConfigurationSegmentWorker ()
{
}

void WaveConfigurationSegmentWorker::setConfigurationSegmentName (const string &configurationSegmentName)
{
    m_configurationSegmentName = configurationSegmentName;
}

string WaveConfigurationSegmentWorker::getConfigurationSegmentName () const
{
    return (m_configurationSegmentName);
}

ManagementInterfaceMessage *WaveConfigurationSegmentWorker::createConfig (WaveConfigurationSegmentCreateContext *pWaveConfigurationSegmentCreateContext)
{
    trace (TRACE_LEVEL_INFO, "WaveConfigurationSegmentWorker::createConfig : Calling the base class function, returning NULL");

    return (NULL);
}

string WaveConfigurationSegmentWorker::getErrorString (ManagementInterfaceMessage* pMessage)
{
    return FrameworkToolKit::localize(pMessage->getCompletionStatus());
}

void WaveConfigurationSegmentWorker::createConfigValidation ()
{
}

ManagementInterfaceMessage *WaveConfigurationSegmentWorker::updateConfig () 
{
    return (NULL);
}

void WaveConfigurationSegmentWorker::updateConfigValidation () 
{
}
        
ManagementInterfaceMessage *WaveConfigurationSegmentWorker::deleteConfig (WaveConfigurationSegmentDeleteContext *pWaveConfigurationSegmentDeleteContext)
{
    return (NULL);
}

void WaveConfigurationSegmentWorker::deleteConfigValidation () 
{
}
        
bool WaveConfigurationSegmentWorker::getIsConfigExistValidationRequired () const
{
    return (m_isConfigExistValidationRequired);
}

void  WaveConfigurationSegmentWorker::setIsConfigExistValidationRequired (const bool isConfigExistValidationRequired)
{
	m_isConfigExistValidationRequired = isConfigExistValidationRequired;
}
}

