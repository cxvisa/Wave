/***************************************************************************
 *   Copyright (C) 2008-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                               *
 ***************************************************************************/

#include "Framework/DistributedLog/DistributedLogUpdateLogIdMessage.h"
#include "Framework/DistributedLog/DistributedLogTypes.h"
#include "Framework/DistributedLog/DistributedLogObjectManager.h"

namespace WaveNs
{

DistributedLogUpdateLogIdMessage::DistributedLogUpdateLogIdMessage ()
    : ManagementInterfaceMessage (DistributedLogObjectManager::getServiceName (), DISTRIBUTED_LOG_UPDATE_IN_MEMORY_LOG_ID)
{
}

DistributedLogUpdateLogIdMessage::~DistributedLogUpdateLogIdMessage ()
{
}

void DistributedLogUpdateLogIdMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
}

}
