/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish                                                      *
 ***************************************************************************/
#include "Framework/Messaging/Local/PrismMessage.h"
#include "Cluster/Local/ClusterLocalReportRemovedNodeFromClusterMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{

/// Name
/// ClusterLocalReportRemovedNodeFromClusterMessage
/// Description
/// Just Calls the base class constructor
/// Constructor
/// Input
/// None
/// Output
/// None
/// Return
/// None

ClusterLocalReportRemovedNodeFromClusterMessage::ClusterLocalReportRemovedNodeFromClusterMessage ()
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_REPORT_NODE_REMOVED_FROM_CLUSTER),
      m_thisNodePort  (0),
      m_thisNodeLocationId(0)
{


}
/// Name
/// ClusterLocalReportRemovedNodeFromClusterMessage
/// Description
/// Non-Default Constructor
/// Input
/// None
/// Output
/// None
/// Return
/// None


ClusterLocalReportRemovedNodeFromClusterMessage::ClusterLocalReportRemovedNodeFromClusterMessage (const string & thisNodeIpAddress,UI32 thisNodePort, LocationId thisNodeLocationId)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_REPORT_NODE_REMOVED_FROM_CLUSTER),m_thisNodeIpAddress(thisNodeIpAddress), m_thisNodePort(thisNodePort), m_thisNodeLocationId(thisNodeLocationId)

{
}
/// Name
/// ClusterLocalReportRemovedNodeFromClusterMessage
/// Description
/// Destructor
/// Input
/// None
/// Output
/// None
/// Return
/// None

ClusterLocalReportRemovedNodeFromClusterMessage::~ClusterLocalReportRemovedNodeFromClusterMessage ()
{
}

//Mutators and Accessors
void ClusterLocalReportRemovedNodeFromClusterMessage::setThisNodeIpAddress(const string &thisNodeIpAddress)
{
    m_thisNodeIpAddress = thisNodeIpAddress;

}

void ClusterLocalReportRemovedNodeFromClusterMessage::setThisNodePort(const UI32 thisNodePort)
{
    m_thisNodePort = thisNodePort;
}


void ClusterLocalReportRemovedNodeFromClusterMessage::setThisNodeLocationId(const UI32 thisLocationId)
{
    m_thisNodeLocationId = thisLocationId;
}

void ClusterLocalReportRemovedNodeFromClusterMessage::setupAttributesForSerialization()
{
    PrismMessage::setupAttributesForSerialization ();
     addSerializableAttribute (new AttributeString      (&m_thisNodeIpAddress,  "thisNodeIpAddress"));
     addSerializableAttribute (new AttributeUI32        (&m_thisNodePort,       "thisNodePort"));
     addSerializableAttribute (new AttributeLocationId  (&m_thisNodeLocationId, "thisNodeLocationId"));
}
string const & ClusterLocalReportRemovedNodeFromClusterMessage::getThisNodeIpAddress() const
{
    return m_thisNodeIpAddress;
}


UI32 ClusterLocalReportRemovedNodeFromClusterMessage::getThisNodePort() const
{
    return m_thisNodePort;
}



LocationId ClusterLocalReportRemovedNodeFromClusterMessage::getThisNodeLocationId() const
{
    return m_thisNodeLocationId;
}

}
