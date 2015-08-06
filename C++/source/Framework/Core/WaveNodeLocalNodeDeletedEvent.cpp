/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/


#include "Framework/Core/WaveNodeLocalNodeDeletedEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

WaveNodeLocalNodeDeletedEvent::WaveNodeLocalNodeDeletedEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_LOCAL_NODE_DELETED_EVENT)
{
}

WaveNodeLocalNodeDeletedEvent::~WaveNodeLocalNodeDeletedEvent ()
{

}

void WaveNodeLocalNodeDeletedEvent::setupAttributesForSerialization ()
{
  PrismEvent::setupAttributesForSerialization ();
}

}
