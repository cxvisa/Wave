/***************************************************************************
 *  @file   : PrimaryChangedEvent.cpp                                      *
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Description : This file defines an event PrimaryChangedEvent which is *
 *                 broadcasted from new Primary and all secondaries in a   *
 *                 cluster when old Primary is failing over. This event is *
 *                 specifically for Plug-ins.                              *
 *   Author      : Pritee Ghosh                                            *
 *   Date        : 03/02/2011                                              *
 ***************************************************************************/


#include "Framework/Core/PrimaryChangedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

PrimaryChangedEvent::PrimaryChangedEvent ()
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_PRIMARY_CHANGED_EVENT),
      m_newPrimaryLocationId (0)
{
}

PrimaryChangedEvent::~PrimaryChangedEvent ()
{
}

void PrimaryChangedEvent::setupAttributesForSerialization ()
{
    WaveEvent::setupAttributesForSerialization ();
}

LocationId PrimaryChangedEvent::getNewPrimaryLocationId () const
{
    return m_newPrimaryLocationId;
}

void PrimaryChangedEvent::setNewPrimaryLocationId (const LocationId location)
{
    m_newPrimaryLocationId = location;
}
}
