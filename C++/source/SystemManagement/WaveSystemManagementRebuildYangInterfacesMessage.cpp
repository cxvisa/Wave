/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementRebuildYangInterfacesMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"

namespace WaveNs
{

WaveSystemManagementRebuildYangInterfacesMessage::WaveSystemManagementRebuildYangInterfacesMessage ()
    : ManagementInterfaceMessage (WaveSystemManagementObjectManager::getClassName (), WAVE_SYSTEM_MANAGEMENT_REBUILD_YANG_INTERFACES)
{
}

WaveSystemManagementRebuildYangInterfacesMessage::~WaveSystemManagementRebuildYangInterfacesMessage ()
{
}

void WaveSystemManagementRebuildYangInterfacesMessage::setupAttributesForSerialization ()
{
        ManagementInterfaceMessage::setupAttributesForSerialization ();
}


}
