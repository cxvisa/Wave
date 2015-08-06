/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  * 
 *   Author - Chaitanya Gangwar                                            *
 ***************************************************************************/
 
#include "Framework/Core/PrismFrameworkReplayConfigMessage.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
 
namespace WaveNs
{

PrismFrameworkReplayConfigMessage::PrismFrameworkReplayConfigMessage ()
    : PrismMessage (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_REPLAY_CONFIG_FILE)
{
}

PrismFrameworkReplayConfigMessage::~PrismFrameworkReplayConfigMessage()
{
}

/*void PrismFrameworkReplayConfigMessage::setConfigFileName (const configFileName)
{
    m_configFileName = configFileName; 
}    

string PrismFrameworkReplayConfigMessage::getConfigFileName ()
{
    return (m_configFileName);
}
*/
}
