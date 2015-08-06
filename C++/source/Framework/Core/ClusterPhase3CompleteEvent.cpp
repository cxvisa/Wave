/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                              *
 ***************************************************************************/


#include "Framework/Core/ClusterPhase3CompleteEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

ClusterPhase3CompleteEvent::ClusterPhase3CompleteEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), FRAMEWORK_OBJECT_MANAGER_BROADCAST_PHASE3_COMPLETE_EVENT)
{
}

ClusterPhase3CompleteEvent::~ClusterPhase3CompleteEvent ()
{
}

void ClusterPhase3CompleteEvent::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();
}

}
