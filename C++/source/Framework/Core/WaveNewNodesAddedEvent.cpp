/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/


#include "Framework/Core/WaveNewNodesAddedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

WaveNewNodesAddedEvent::WaveNewNodesAddedEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (),FRAMEWORK_OBJECT_MANAGER_BROADCAST_ADDITION_OF_NEW_NODES_EVENT )
{
}

WaveNewNodesAddedEvent::~WaveNewNodesAddedEvent ()
{
}

void WaveNewNodesAddedEvent::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();
}

void WaveNewNodesAddedEvent::addNewNodeDetails (const LocationId &locationId, const string &ipAddress, const UI32 &port)
{
  m_locationIdsForNewNodes.push_back(locationId);
  m_IpAddressesForNewNodes.push_back(ipAddress);
  m_portsForNewNodes.push_back(port);
}

UI32 WaveNewNodesAddedEvent::getNumberOfNewLocations () const
{
  return m_locationIdsForNewNodes.size();
    
}

LocationId  WaveNewNodesAddedEvent::getLocationIdAtIndex        (const UI32 &index) const
{
  return m_locationIdsForNewNodes[index];
}

string WaveNewNodesAddedEvent::getIpAddressAtIndex         (const UI32 &index) const
{
    return m_IpAddressesForNewNodes[index];
}

UI32 WaveNewNodesAddedEvent::getPortAtIndex              (const UI32 &index) const
{
     return m_portsForNewNodes[index];
}
}
