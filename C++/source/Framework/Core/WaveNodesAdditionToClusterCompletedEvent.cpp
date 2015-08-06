/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Sudhakar Jha                                              *
 ***************************************************************************/


#include "Framework/Core/WaveNodesAdditionToClusterCompletedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

WaveNodesAdditionToClusterCompletedEvent::WaveNodesAdditionToClusterCompletedEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_NODES_ADDITION_TO_CLUSTER_COMPLETED_EVENT )
{
}

WaveNodesAdditionToClusterCompletedEvent::~WaveNodesAdditionToClusterCompletedEvent ()
{
}

void WaveNodesAdditionToClusterCompletedEvent::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();
}

void WaveNodesAdditionToClusterCompletedEvent::addNewNodeDetails (const LocationId &locationId, const string &ipAddress, const UI32 &port)
{
  m_locationIdsForNewNodes.push_back(locationId);
  m_IpAddressesForNewNodes.push_back(ipAddress);
  m_portsForNewNodes.push_back(port);
}

UI32 WaveNodesAdditionToClusterCompletedEvent::getNumberOfNewLocations () const
{
  return m_locationIdsForNewNodes.size();
    
}

LocationId  WaveNodesAdditionToClusterCompletedEvent::getLocationIdAtIndex (const UI32 &index) const
{
  return m_locationIdsForNewNodes[index];
}

string WaveNodesAdditionToClusterCompletedEvent::getIpAddressAtIndex  (const UI32 &index) const
{
    return m_IpAddressesForNewNodes[index];
}

UI32 WaveNodesAdditionToClusterCompletedEvent::getPortAtIndex  (const UI32 &index) const
{
     return m_portsForNewNodes[index];
}
}

