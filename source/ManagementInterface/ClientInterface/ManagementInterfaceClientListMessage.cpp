/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Chaitanya Gangwar                                            *
 ***************************************************************************/

#include "ManagementInterface/ClientInterface/ManagementInterfaceClientListMessage.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "ManagementInterface/ManagementInterfaceTypes.h"
#include "ManagementInterface/ManagementInterfaceObjectManager.h"

namespace WaveNs
{

ManagementInterfaceClientListMessage::ManagementInterfaceClientListMessage ()
    : ManagementInterfaceMessage (ManagementInterfaceObjectManager::getServiceName (), MANAGEMENTINTERFACE_CLIENT_LIST)
{
}

ManagementInterfaceClientListMessage::~ManagementInterfaceClientListMessage ()
{
}

void ManagementInterfaceClientListMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeStringVector (&m_connectedClients, "connectedClients"));
}

void ManagementInterfaceClientListMessage::setConnectedClients (vector<string> connectedClients)
{
    m_connectedClients = connectedClients;
}

vector<string> ManagementInterfaceClientListMessage::getConnectedClients ()
{
    return (m_connectedClients);
}

}
