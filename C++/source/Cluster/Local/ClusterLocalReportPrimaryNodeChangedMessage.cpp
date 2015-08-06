/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish                                                      *
 ***************************************************************************/
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Cluster/Local/ClusterLocalReportPrimaryNodeChangedMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{
/// Name
/// ClusterLocalReportPrimaryNodeChangedMessage
/// Description
/// Just Calls the base class constructor
/// Constructor
/// Input
/// None
/// Output
/// None
/// Return
/// None
ClusterLocalReportPrimaryNodeChangedMessage::ClusterLocalReportPrimaryNodeChangedMessage ()
    : WaveMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_REPORT_PRIMARY_NODE_CHANGED),
      m_thisNodeIpAddress(""),
      m_thisNodePort(0),
      m_thisNodeLocationId(0)
{


}

/// Name
/// ClusterLocalReportPrimaryNodeChangedMessage
/// Description
/// Non-Default Constructor
/// Input
/// None
/// Output
/// None
/// Return
/// None
ClusterLocalReportPrimaryNodeChangedMessage::ClusterLocalReportPrimaryNodeChangedMessage (const string & thisNodeIpAddress,
                                                                                          const UI32   thisNodePort,
                                                                                          const LocationId   thisNodeLocationId)
    : WaveMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_REPORT_PRIMARY_NODE_CHANGED),
      m_thisNodeIpAddress(thisNodeIpAddress),
      m_thisNodePort(thisNodePort),
      m_thisNodeLocationId(thisNodeLocationId)

{
}

/// Name
/// ClusterLocalReportPrimaryNodeChangedMessage
/// Description
/// Destructor
/// Input
/// None
/// Output
/// None
/// Return
/// None
ClusterLocalReportPrimaryNodeChangedMessage::~ClusterLocalReportPrimaryNodeChangedMessage ()
{
}


//Accessors and Mutators for fields related to LocalNode Info as well as primary node info



void ClusterLocalReportPrimaryNodeChangedMessage::setThisNodeIpAddress(const string &thisNodeIpAddress)
{
    m_thisNodeIpAddress = thisNodeIpAddress;

}

void ClusterLocalReportPrimaryNodeChangedMessage::setThisNodePort(const UI32 thisNodePort)
{
    m_thisNodePort = thisNodePort;
}

void ClusterLocalReportPrimaryNodeChangedMessage::setThisNodeLocationId(const UI32 thisLocationId)
{
    m_thisNodeLocationId = thisLocationId;
}

void ClusterLocalReportPrimaryNodeChangedMessage::setupAttributesForSerialization ()
{
     WaveMessage::setupAttributesForSerialization ();
      addSerializableAttribute (new AttributeString     (&m_thisNodeIpAddress,  "thisNodeIpAddress"));
      addSerializableAttribute (new AttributeUI32       (&m_thisNodePort,       "thisNodePort"));
      addSerializableAttribute (new AttributeLocationId (&m_thisNodeLocationId, "thisNodeLocationId"));
}

string const & ClusterLocalReportPrimaryNodeChangedMessage::getThisNodeIpAddress() const
{
    return m_thisNodeIpAddress;
}


UI32 ClusterLocalReportPrimaryNodeChangedMessage::getThisNodePort() const
{
    return m_thisNodePort;
}


LocationId ClusterLocalReportPrimaryNodeChangedMessage::getThisNodeLocationId() const
{
    return m_thisNodeLocationId;
}

}
