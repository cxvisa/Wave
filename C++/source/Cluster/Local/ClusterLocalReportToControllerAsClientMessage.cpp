/**************************************************************************
*   Copyright (C) 2005-2014 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author : Himanshu Varshney                                            *
***************************************************************************/

#include "Cluster/Local/ClusterLocalReportToControllerAsClientMessage.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Framework/Attributes/AttributeIpVxAddress.h"

namespace WaveNs
{   

ClusterLocalReportToControllerAsClientMessage::ClusterLocalReportToControllerAsClientMessage ()
    : ManagementInterfaceMessage (ClusterLocalObjectManager::getPrismServiceName (), CLUSTER_LOCAL_REPORT_AS_CLIENT_MESSAGE)
{
    m_controllerPort = 0;
    m_controllerClientPort     = 0;
}
    
ClusterLocalReportToControllerAsClientMessage::~ClusterLocalReportToControllerAsClientMessage ()
{
}

void ClusterLocalReportToControllerAsClientMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeIpVxAddress (&m_controllerIpAddress, "controllerIpAddress"));
    addSerializableAttribute (new AttributeIpVxAddress (&m_controllerClientIpAddress,     "controllerClientIpAddress"));
    addSerializableAttribute (new AttributeSI32        (&m_controllerPort,      "controllerPort"));
    addSerializableAttribute (new AttributeSI32        (&m_controllerClientPort,          "controllerClientPort"));
}

void ClusterLocalReportToControllerAsClientMessage::setControllerIpAddress (const IpVxAddress &ipAddress)
{
    m_controllerIpAddress = ipAddress;
}

IpVxAddress ClusterLocalReportToControllerAsClientMessage::getControllerIpAddress ()
{
    return (m_controllerIpAddress);
}

void ClusterLocalReportToControllerAsClientMessage::setControllerClientIpAddress (const IpVxAddress &ipAddress)
{
    m_controllerClientIpAddress = ipAddress;
}

IpVxAddress ClusterLocalReportToControllerAsClientMessage::getControllerClientIpAddress ()
{
    return (m_controllerClientIpAddress);
}

SI32 ClusterLocalReportToControllerAsClientMessage::getControllerPort ()
{
    return (m_controllerPort);
}

void ClusterLocalReportToControllerAsClientMessage::setControllerPort (const SI32 &port)
{
    m_controllerPort = port;
}


SI32 ClusterLocalReportToControllerAsClientMessage::getControllerClientPort ()
{
    return (m_controllerClientPort);
}

void ClusterLocalReportToControllerAsClientMessage::setControllerClientPort (const SI32 &port)
{
    m_controllerClientPort = port;
}

}
 
