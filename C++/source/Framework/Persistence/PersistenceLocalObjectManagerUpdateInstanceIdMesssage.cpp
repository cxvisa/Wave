/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerUpdateInstanceIdMesssage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerUpdateInstanceIdMesssage::PersistenceLocalObjectManagerUpdateInstanceIdMesssage ()
    : WaveMessage(PersistenceLocalObjectManager::getWaveServiceId(), PERSISTENCE_LOCAL_OBJECT_MANAGER_UPDATE_INSTANCE_ID)
{

}

PersistenceLocalObjectManagerUpdateInstanceIdMesssage::~PersistenceLocalObjectManagerUpdateInstanceIdMesssage ()
{

}

}
