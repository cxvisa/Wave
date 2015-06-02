/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "LockManagement/LockManagementObjectManagerTypes.h"
#include "LockManagement/LockManagementObjectManagerReleaseLockMessage.h"
#include "LockManagement/LockManagementObjectManager.h"

namespace WaveNs
{

LockManagementObjectManagerReleaseLockMessage::LockManagementObjectManagerReleaseLockMessage ()
    : ManagementInterfaceMessage      (LockManagementObjectManager::getClassName (), LOCK_MANAGEMENT_OBJECT_MANAGER_RELEASE_LOCK)
{
}

LockManagementObjectManagerReleaseLockMessage::LockManagementObjectManagerReleaseLockMessage (const string &serviceString)
    : ManagementInterfaceMessage      (LockManagementObjectManager::getClassName (), LOCK_MANAGEMENT_OBJECT_MANAGER_RELEASE_LOCK),
        m_serviceString (serviceString)
{
}

LockManagementObjectManagerReleaseLockMessage::~LockManagementObjectManagerReleaseLockMessage ()
{
}

void LockManagementObjectManagerReleaseLockMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_serviceString, "serviceString"));
}

const string& LockManagementObjectManagerReleaseLockMessage::getServiceString ()
{
    return m_serviceString;
}

}
