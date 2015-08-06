 /**************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh		                                       *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalSlotRemoveMessage.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Framework/Utils/FrameworkToolKit.h"


namespace WaveNs
{

ClusterLocalSlotRemoveMessage::ClusterLocalSlotRemoveMessage ()
: PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SLOT_REMOVE_MESSAGE),
    m_slotNumber (0),
    m_hwType (0x10) // hardcoded for SYS_SLOT_LC
{
    m_locationId = FrameworkToolKit::getThisLocationId ();
}
    
ClusterLocalSlotRemoveMessage::ClusterLocalSlotRemoveMessage (const UI32 &slotNumber)
        : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SLOT_REMOVE_MESSAGE),
        m_slotNumber (slotNumber),
        m_hwType (0x10) // hardcoded for SYS_SLOT_LC
{
    m_locationId = FrameworkToolKit::getThisLocationId ();
}

ClusterLocalSlotRemoveMessage::ClusterLocalSlotRemoveMessage (const UI32 &slotNumber, const UI32 &hwType)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SLOT_REMOVE_MESSAGE),
        m_slotNumber (slotNumber),
        m_hwType (hwType)
{
    m_locationId = FrameworkToolKit::getThisLocationId ();
}

ClusterLocalSlotRemoveMessage::ClusterLocalSlotRemoveMessage (const UI32 &slotNumber, const UI32 &hwType, const LocationId &locationId)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_SLOT_REMOVE_MESSAGE),
        m_slotNumber (slotNumber),
        m_hwType (hwType),
        m_locationId (locationId)
{
}

void ClusterLocalSlotRemoveMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32        (&m_slotNumber,     "slotNumber"));
     addSerializableAttribute (new AttributeUI32        (&m_hwType,         "hwType"));
     addSerializableAttribute (new AttributeLocationId  (&m_locationId,     "locationId"));
}

ClusterLocalSlotRemoveMessage::~ClusterLocalSlotRemoveMessage ()
{
}

UI32 ClusterLocalSlotRemoveMessage::getSlotNumber ()
{
    return m_slotNumber;
}

void ClusterLocalSlotRemoveMessage::setSlotNumber (const  UI32 &slotNumber)
{
    m_slotNumber = slotNumber;
}

UI32 ClusterLocalSlotRemoveMessage::getHwType ()
{
    return m_hwType;
}

void ClusterLocalSlotRemoveMessage::setHwType (const  UI32 &hwType)
{
    m_hwType = hwType;
}

LocationId ClusterLocalSlotRemoveMessage::getLocationId ()
{
    return m_locationId;
}

void ClusterLocalSlotRemoveMessage::setLocationId (const LocationId &locationId)
{
    m_locationId = locationId;
}



}

