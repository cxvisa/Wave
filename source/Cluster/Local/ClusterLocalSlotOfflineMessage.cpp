 /**************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh		                                       *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalSlotOfflineMessage.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"
#include "Cluster/Local/ClusterLocalTypes.h"


namespace WaveNs
{

ClusterLocalSlotOfflineMessage::ClusterLocalSlotOfflineMessage ()
    : PrismMessage (ClusterLocalObjectManager::getPrismServiceId (), CLUSTER_LOCAL_SLOT_OFFLINE_MESSAGE),
    m_slotNumber (0),
    m_hwType (0x10),
    m_slotState (0)
{
}

ClusterLocalSlotOfflineMessage::ClusterLocalSlotOfflineMessage (const UI32 &slotNumber, const UI32 &hwType, const UI32 &slotState)
    : PrismMessage (ClusterLocalObjectManager::getPrismServiceId (), CLUSTER_LOCAL_SLOT_OFFLINE_MESSAGE),
    m_slotNumber (slotNumber),
    m_hwType (hwType),
    m_slotState (slotState)
{
}

ClusterLocalSlotOfflineMessage::~ClusterLocalSlotOfflineMessage ()
{
}

void ClusterLocalSlotOfflineMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeUI32   (&m_slotNumber,  "slotNumber"));
     addSerializableAttribute (new AttributeUI32   (&m_hwType,      "hwType"));
     addSerializableAttribute (new AttributeUI32   (&m_slotState,   "slotState"));
}

UI32 ClusterLocalSlotOfflineMessage::getSlotNumber () const
{
    return (m_slotNumber);
}

void ClusterLocalSlotOfflineMessage::setSlotNumber (const UI32 &slotNumber)
{
    m_slotNumber = slotNumber;
}

UI32 ClusterLocalSlotOfflineMessage::getSlotState() const
{
    return (m_slotState);
}

void ClusterLocalSlotOfflineMessage::setSlotState (const UI32 &slotState)
{
    m_slotState = slotState;
}

UI32 ClusterLocalSlotOfflineMessage::getHwType () const
{
    return (m_hwType);
}

void ClusterLocalSlotOfflineMessage::setHwType (const UI32 &hwType)
{
    m_hwType = hwType;
}


}

