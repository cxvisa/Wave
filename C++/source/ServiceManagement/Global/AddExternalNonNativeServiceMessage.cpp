/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/AddExternalNonNativeServiceMessage.h"
#include "ServiceManagement/Global/ServiceManagementTypes.h"
#include "ServiceManagement/Global/ServiceManagementObjectManager.h"

namespace WaveNs
{

AddExternalNonNativeServiceMessage::AddExternalNonNativeServiceMessage ()
    : ManagementInterfaceMessage (ServiceManagementObjectManager::getServiceName (), SERVCIE_MANAGEMENT_ADD_EXTERNAL_NON_NATIVE_SERVICE)
{
}

AddExternalNonNativeServiceMessage::~AddExternalNonNativeServiceMessage ()
{
}

void AddExternalNonNativeServiceMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeString (&m_name, "name"));
}

}
