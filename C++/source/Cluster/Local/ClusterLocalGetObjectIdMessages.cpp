/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Cluster/Local/ClusterLocalGetObjectIdMessages.h"
#include "Cluster/Local/ClusterLocalTypes.h"
#include "Cluster/Local/ClusterLocalObjectManager.h"

namespace WaveNs
{

ClusterLocalGetSlotObjectIdMessage::ClusterLocalGetSlotObjectIdMessage (const UI32 &slotNumber, const LocationId &locationId)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_GET_SLOT_OBJECTID),
        m_slotNumber (slotNumber),
        m_locationId (locationId)
{
}

ClusterLocalGetSlotObjectIdMessage::~ClusterLocalGetSlotObjectIdMessage ()
{
}

UI32 ClusterLocalGetSlotObjectIdMessage::getSlotNumber () const
{
    return (m_slotNumber);
}

void ClusterLocalGetSlotObjectIdMessage::setSlotNumber (const UI32 &slotNumber)
{
    m_slotNumber = slotNumber;
}

LocationId ClusterLocalGetSlotObjectIdMessage::getLocationId () const
{
    return (m_locationId);
}

void ClusterLocalGetSlotObjectIdMessage::setLocationId (const LocationId &locationId)
{
    m_locationId = locationId;
}

ObjectId ClusterLocalGetSlotObjectIdMessage::getSlotObjectId () const
{
    return (m_slotObjectId);
}

void ClusterLocalGetSlotObjectIdMessage::setSlotObjectId (const ObjectId slotObjectId)
{
    m_slotObjectId = slotObjectId;
}

ClusterLocalGetLocationObjectIdMessage::ClusterLocalGetLocationObjectIdMessage (const LocationId &locationId)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_GET_LOCATION_OBJECTID),
        m_locationId (locationId)
{
}

ClusterLocalGetLocationObjectIdMessage::~ClusterLocalGetLocationObjectIdMessage ()
{
}

LocationId ClusterLocalGetLocationObjectIdMessage::getLocationId () const
{
    return (m_locationId);
}

void ClusterLocalGetLocationObjectIdMessage::setLocationId (const LocationId &locationId)
{
    m_locationId = locationId;
}

ObjectId ClusterLocalGetLocationObjectIdMessage::getLocationObjectId () const
{
    return (m_locationObjectId);
}

void ClusterLocalGetLocationObjectIdMessage::setLocationObjectId (const ObjectId locationObjectId)
{
    m_locationObjectId = locationObjectId;
}

ClusterLocalGetLocationIdMessage::ClusterLocalGetLocationIdMessage (const ObjectId locationObjectId)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_GET_LOCATIONID),
        m_locationObjectId (locationObjectId)
{
}

ClusterLocalGetLocationIdMessage::~ClusterLocalGetLocationIdMessage ()
{
}

LocationId ClusterLocalGetLocationIdMessage::getLocationId () const
{
    return (m_locationId);
}

void ClusterLocalGetLocationIdMessage::setLocationId (const LocationId &locationId)
{
    m_locationId = locationId;
}

ObjectId ClusterLocalGetLocationIdMessage::getLocationObjectId () const
{
    return (m_locationObjectId);
}

void ClusterLocalGetLocationIdMessage::setLocationObjectId (const ObjectId locationObjectId)
{
    m_locationObjectId = locationObjectId;
}

ClusterLocalGetSlotNumberMessage::ClusterLocalGetSlotNumberMessage (const ObjectId slotObjectId)
    : PrismMessage (ClusterLocalObjectManager::getWaveServiceId (), CLUSTER_LOCAL_GET_SLOTNUMBER),
        m_slotObjectId (slotObjectId)
{
}

ClusterLocalGetSlotNumberMessage::~ClusterLocalGetSlotNumberMessage ()
{
}

UI32 ClusterLocalGetSlotNumberMessage::getSlotNumber () const
{
    return (m_slotNumber);
}

void ClusterLocalGetSlotNumberMessage::setSlotNumber (const UI32 &slotNumber)
{
    m_slotNumber = slotNumber;
}

ObjectId ClusterLocalGetSlotNumberMessage::getSlotObjectId () const
{
    return (m_slotObjectId);
}

void ClusterLocalGetSlotNumberMessage::setSlotObjectId (const ObjectId slotObjectId)
{
    m_slotObjectId = slotObjectId;
}

}
