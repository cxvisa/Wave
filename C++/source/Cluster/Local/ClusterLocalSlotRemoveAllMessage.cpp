 /**************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh		                                       *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalSlotRemoveAllMessage.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Framework/Utils/FrameworkToolKit.h"


namespace WaveNs
{

ClusterLocalSlotRemoveAllMessage::ClusterLocalSlotRemoveAllMessage ()
: PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SLOT_REMOVE_ALL_MESSAGE),
  m_hwType (0x10) // hardcoded for SYS_SLOT_LC
{
    m_locationId = FrameworkToolKit::getThisLocationId ();
}
    
ClusterLocalSlotRemoveAllMessage::ClusterLocalSlotRemoveAllMessage (const LocationId &locationId)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SLOT_REMOVE_ALL_MESSAGE),
      m_locationId (locationId), 
      m_hwType (0x10) // hardcoded for SYS_SLOT_LC
{
}

ClusterLocalSlotRemoveAllMessage::ClusterLocalSlotRemoveAllMessage (const LocationId &locationId, const UI32 &hwType)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SLOT_REMOVE_ALL_MESSAGE),
      m_locationId (locationId), 
      m_hwType (hwType)
{
}

void ClusterLocalSlotRemoveAllMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeLocationId  (&m_locationId, "locationId"));
     addSerializableAttribute (new AttributeUI32        (&m_hwType,     "hwType"));
}

ClusterLocalSlotRemoveAllMessage::~ClusterLocalSlotRemoveAllMessage ()
{
}

LocationId ClusterLocalSlotRemoveAllMessage::getLocationId ()
{
    return m_locationId;
}

void ClusterLocalSlotRemoveAllMessage::setLocationId (const LocationId &locationId)
{
    m_locationId = locationId;
}

UI32 ClusterLocalSlotRemoveAllMessage::getHwType ()
{
    return m_hwType;
}

void ClusterLocalSlotRemoveAllMessage::setHwType (const  UI32 &hwType)
{
    m_hwType = hwType;
}

}

