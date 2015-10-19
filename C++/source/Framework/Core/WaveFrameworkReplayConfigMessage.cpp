/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  * 
 *   Author - Chaitanya Gangwar                                            *
 ***************************************************************************/
 
#include "Framework/Core/WaveFrameworkReplayConfigMessage.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
 
namespace WaveNs
{

WaveFrameworkReplayConfigMessage::WaveFrameworkReplayConfigMessage ()
    : WaveMessage (WaveFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REPLAY_CONFIG_FILE)
{
}

WaveFrameworkReplayConfigMessage::~WaveFrameworkReplayConfigMessage()
{
}

/*void WaveFrameworkReplayConfigMessage::setConfigFileName (const configFileName)
{
    m_configFileName = configFileName; 
}    

string WaveFrameworkReplayConfigMessage::getConfigFileName ()
{
    return (m_configFileName);
}
*/
}
