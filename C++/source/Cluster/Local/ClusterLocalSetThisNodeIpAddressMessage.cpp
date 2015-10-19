/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalSetThisNodeIpAddressMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{

ClusterLocalSetThisNodeIpAddressMessage::ClusterLocalSetThisNodeIpAddressMessage ()
    : ManagementInterfaceMessage (ClusterLocalObjectManager::getWaveServiceName (), CLUSTER_LOCAL_SET_THIS_NODE_IP_ADDRESS),
      m_ipAddress                ("")
{
}

ClusterLocalSetThisNodeIpAddressMessage::ClusterLocalSetThisNodeIpAddressMessage (const string &ipAddress)
    : ManagementInterfaceMessage (ClusterLocalObjectManager::getWaveServiceName (), CLUSTER_LOCAL_SET_THIS_NODE_IP_ADDRESS),
      m_ipAddress                (ipAddress)
{
}

ClusterLocalSetThisNodeIpAddressMessage::~ClusterLocalSetThisNodeIpAddressMessage ()
{
}

string ClusterLocalSetThisNodeIpAddressMessage::getIpAddress () const
{
    return (m_ipAddress);
}

void ClusterLocalSetThisNodeIpAddressMessage::setIpAddress (const string &ipAddress)
{
    m_ipAddress = ipAddress;
}

}
