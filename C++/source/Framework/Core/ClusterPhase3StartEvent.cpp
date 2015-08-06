/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Anil ChannaveeraSetty                                        *
 ***************************************************************************/


#include "Framework/Core/ClusterPhase3StartEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

ClusterPhase3StartEvent::ClusterPhase3StartEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_BROADCAST_PHASE3_START_EVENT)
{
}

ClusterPhase3StartEvent::~ClusterPhase3StartEvent ()
{
}

void ClusterPhase3StartEvent::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();
}

}
