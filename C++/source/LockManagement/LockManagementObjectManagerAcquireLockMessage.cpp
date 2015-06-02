/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "LockManagement/LockManagementObjectManagerTypes.h"
#include "LockManagement/LockManagementObjectManagerAcquireLockMessage.h"
#include "LockManagement/LockManagementObjectManager.h"

namespace WaveNs
{

LockManagementObjectManagerAcquireLockMessage::LockManagementObjectManagerAcquireLockMessage ()
    : ManagementInterfaceMessage (LockManagementObjectManager::getClassName (), LOCK_MANAGEMENT_OBJECT_MANAGER_ACQUIRE_LOCK)
{
}

LockManagementObjectManagerAcquireLockMessage::LockManagementObjectManagerAcquireLockMessage (const string &serviceString)
        : ManagementInterfaceMessage (LockManagementObjectManager::getClassName (), LOCK_MANAGEMENT_OBJECT_MANAGER_ACQUIRE_LOCK),
          m_serviceString (serviceString)
{
}

LockManagementObjectManagerAcquireLockMessage::~LockManagementObjectManagerAcquireLockMessage ()
{
}

void LockManagementObjectManagerAcquireLockMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_serviceString, "serviceString"));
}

const string& LockManagementObjectManagerAcquireLockMessage::getServiceString ()
{
    return m_serviceString;
}

}
