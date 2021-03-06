/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerInitializeBeforeBootCompleteMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"

namespace WaveNs
{

PersistenceObjectManagerInitializeBeforeBootCompleteMessage::PersistenceObjectManagerInitializeBeforeBootCompleteMessage ()
    : WaveMessage(PersistenceObjectManager::getWaveServiceId(), PERSISTENCE_OBJECT_MANAGER_INITIALIZE_BEFORE_BOOT_COMPLETE)
{

}

PersistenceObjectManagerInitializeBeforeBootCompleteMessage::~PersistenceObjectManagerInitializeBeforeBootCompleteMessage ()
{

}

}
