/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/


#include "Framework/Core/WaveNodeDeleteClusterEvent.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

WaveNodeDeleteClusterEvent::WaveNodeDeleteClusterEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getPrismServiceId (), FRAMEWORK_OBJECT_MANAGER_DELETE_CLUSTER_EVENT),
      m_isRebootRequired (true)
{
}

WaveNodeDeleteClusterEvent::~WaveNodeDeleteClusterEvent ()
{

}

void WaveNodeDeleteClusterEvent::setupAttributesForSerialization ()
{
  PrismEvent::setupAttributesForSerialization ();
}

void WaveNodeDeleteClusterEvent::setIsRebootRequired (const bool &isRebootRequired)
{
    m_isRebootRequired = isRebootRequired;
}

bool WaveNodeDeleteClusterEvent::getIsRebootRequired () const
{
    return (m_isRebootRequired);
}

}
