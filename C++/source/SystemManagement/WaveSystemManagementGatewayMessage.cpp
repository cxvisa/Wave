/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementGatewayMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"

namespace WaveNs
{

WaveSystemManagementGatewayMessage::WaveSystemManagementGatewayMessage ()
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_GATEWAY_MESSAGE)
{
}

WaveSystemManagementGatewayMessage::~WaveSystemManagementGatewayMessage ()
{
}

void WaveSystemManagementGatewayMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_writeInputArguments,      "writeInputArguments"));
    addSerializableAttribute (new AttributeString (&m_writeSubMode,             "writeSubMode"));
    addSerializableAttribute (new AttributeString (&m_errorString,              "errorString"));
    addSerializableAttribute (new AttributeBool   (&m_isWyserEaCompatibilityMode, "isWyserEaCompatibilityMode"));
}

string WaveSystemManagementGatewayMessage::getWriteInputArguments ()
{
    return (m_writeInputArguments);
}
        
void WaveSystemManagementGatewayMessage::setWriteInputArguments (string writeInputArguments)
{
    m_writeInputArguments = writeInputArguments;
}

string WaveSystemManagementGatewayMessage::getWriteSubMode ()
{
    return (m_writeSubMode);
}
        
void WaveSystemManagementGatewayMessage::setWriteSubMode (string writeSubMode)
{
    m_writeSubMode = writeSubMode;
}

string WaveSystemManagementGatewayMessage::getCommandErrorString () const
{
    return (m_errorString);
}

void WaveSystemManagementGatewayMessage::setCommandErrorString (const string &errorString)
{
	m_errorString = errorString;
}

bool WaveSystemManagementGatewayMessage::getIsWyserEaCompatibilityMode() const
{
    return (m_isWyserEaCompatibilityMode);
}

void WaveSystemManagementGatewayMessage::setIsWyserEaCompatibilityMode (const bool &isWyserEaCompatibilityMode)
{
	m_isWyserEaCompatibilityMode = isWyserEaCompatibilityMode;
}


}
