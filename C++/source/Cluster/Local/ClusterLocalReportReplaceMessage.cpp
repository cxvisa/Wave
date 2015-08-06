/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Cluster/Local/ClusterLocalReportReplaceMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{
/// Name
/// ClusterLocalReportReplaceMessage
/// Description
/// Just Calls the base class constructor
/// Constructor
/// Input
/// None
/// Output
/// None
/// Return
/// None
ClusterLocalReportReplaceMessage::ClusterLocalReportReplaceMessage ()
    : WaveMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_REPORT_REPLACE),
      m_thisNodeIpAddress(""),
      m_thisNodePort(0),
      m_thisNodeLocationId(0),
      m_replacedNodeLocationId(0)
{


}

/// Name
/// ClusterLocalReportReplaceMessage
/// Description
/// Non-Default Constructor
/// Input
/// None
/// Output
/// None
/// Return
/// None
ClusterLocalReportReplaceMessage::ClusterLocalReportReplaceMessage (const string & thisNodeIpAddress,
                                                                                          const UI32   thisNodePort,
                                                                                          const LocationId   thisNodeLocationId,
                                                                                          const LocationId   replacedNodeLocationId)
    : WaveMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_REPORT_REPLACE),
      m_thisNodeIpAddress(thisNodeIpAddress),
      m_thisNodePort(thisNodePort),
      m_thisNodeLocationId(thisNodeLocationId),
      m_replacedNodeLocationId(replacedNodeLocationId)

{
}

/// Name
/// ClusterLocalReportReplaceMessage
/// Description
/// Destructor
/// Input
/// None
/// Output
/// None
/// Return
/// None
ClusterLocalReportReplaceMessage::~ClusterLocalReportReplaceMessage ()
{
}


//Accessors and Mutators for fields related to LocalNode Info as well as primary node info



void ClusterLocalReportReplaceMessage::setThisNodeIpAddress(const string &thisNodeIpAddress)
{
    m_thisNodeIpAddress = thisNodeIpAddress;

}

void ClusterLocalReportReplaceMessage::setThisNodePort(const UI32 thisNodePort)
{
    m_thisNodePort = thisNodePort;
}

void ClusterLocalReportReplaceMessage::setThisNodeLocationId(const UI32 thisLocationId)
{
    m_thisNodeLocationId = thisLocationId;
}

void ClusterLocalReportReplaceMessage::setReplacedNodeLocationId(const UI32 replacedLocationId)
{
    m_replacedNodeLocationId = replacedLocationId;
}

void ClusterLocalReportReplaceMessage::setupAttributesForSerialization ()
{
     WaveMessage::setupAttributesForSerialization ();
      addSerializableAttribute (new AttributeString     (&m_thisNodeIpAddress,      "thisNodeIpAddress"));
      addSerializableAttribute (new AttributeUI32       (&m_thisNodePort,           "thisNodePort"));
      addSerializableAttribute (new AttributeLocationId (&m_thisNodeLocationId,     "thisNodeLocationId"));
      addSerializableAttribute (new AttributeLocationId (&m_replacedNodeLocationId, "replacedNodeLocationId"));
}

string const & ClusterLocalReportReplaceMessage::getThisNodeIpAddress() const
{
    return m_thisNodeIpAddress;
}


UI32 ClusterLocalReportReplaceMessage::getThisNodePort() const
{
    return m_thisNodePort;
}


LocationId ClusterLocalReportReplaceMessage::getThisNodeLocationId() const
{
    return m_thisNodeLocationId;
}

LocationId ClusterLocalReportReplaceMessage::getReplacedNodeLocationId() const
{
    return m_replacedNodeLocationId;
}

}
