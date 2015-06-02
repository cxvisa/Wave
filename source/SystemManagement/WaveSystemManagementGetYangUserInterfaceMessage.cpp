/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementGetYangUserInterfaceMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"

namespace WaveNs
{

WaveSystemManagementGetYangUserInterfaceMessage::WaveSystemManagementGetYangUserInterfaceMessage ()
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_GET_YANG_USER_INTERFACE)
{
}

WaveSystemManagementGetYangUserInterfaceMessage::~WaveSystemManagementGetYangUserInterfaceMessage ()
{
}

string &WaveSystemManagementGetYangUserInterfaceMessage::getYangUserInterface ()
{
    return (m_yangUserInterface);
}

}
