/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : acshetty                                                     *
 ***************************************************************************/

#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManagerTypes.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManagerMessages.h"

namespace WaveNs
{

WaveUpdateClientStatusMessage::WaveUpdateClientStatusMessage()
: ManagementInterfaceMessage (WaveUserInterfaceObjectManager::getPrismServiceName (), WAVE_UPDATE_CLIENT_STATUS),
  m_terminalMonitorStatus (false)
{
}

WaveUpdateClientStatusMessage::WaveUpdateClientStatusMessage( const bool terminalMonitorStatus)
: ManagementInterfaceMessage (WaveUserInterfaceObjectManager::getPrismServiceName (), WAVE_UPDATE_CLIENT_STATUS),
  m_terminalMonitorStatus (terminalMonitorStatus)
{
}

WaveUpdateClientStatusMessage::~WaveUpdateClientStatusMessage ()
{
}

void WaveUpdateClientStatusMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_terminalMonitorStatus, "terminalMonitorStatus"));
}

bool WaveUpdateClientStatusMessage::getTerminalMonitorStatus () const
{
    return (m_terminalMonitorStatus);
}

void WaveUpdateClientStatusMessage::setTerminalMonitorStatus (const bool &terminalMonitorStatus)
{
    m_terminalMonitorStatus = terminalMonitorStatus;
}

}
