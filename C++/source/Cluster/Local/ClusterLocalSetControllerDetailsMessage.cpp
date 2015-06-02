/**************************************************************************
*   Copyright (C) 2005-2014 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author : Himanshu Varshney                                            *
***************************************************************************/

#include "Cluster/Local/ClusterLocalSetControllerDetailsMessage.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Framework/Attributes/AttributeIpVxAddress.h"

namespace WaveNs
{

ClusterLocalSetControllerDetailsMessage::ClusterLocalSetControllerDetailsMessage ()
    : ManagementInterfaceMessage (ClusterLocalObjectManager::getPrismServiceName (), CLUSTER_LOCAL_SET_CONTROLLER_DETAILS_MESSAGE)
{
    m_controllerPort = 0;
}

ClusterLocalSetControllerDetailsMessage::~ClusterLocalSetControllerDetailsMessage ()
{
}

void ClusterLocalSetControllerDetailsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeIpVxAddress (&m_controllerIpAddress, "controllerIpAddress"));
    addSerializableAttribute (new AttributeSI32        (&m_controllerPort,      "controllerPort"));
}

void ClusterLocalSetControllerDetailsMessage::setControllerIpAddress (const IpVxAddress &ipAddress)
{
    m_controllerIpAddress = ipAddress;
}

IpVxAddress ClusterLocalSetControllerDetailsMessage::getControllerIpAddress ()
{
    return (m_controllerIpAddress);
}

SI32 ClusterLocalSetControllerDetailsMessage::getControllerPort ()
{
    return (m_controllerPort);
}

void ClusterLocalSetControllerDetailsMessage::setControllerPort (const SI32 &port)
{
    m_controllerPort = port;
}

}


