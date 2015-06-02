/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerUpdateInstanceIdMesssage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"

namespace WaveNs
{

PersistenceObjectManagerUpdateInstanceIdMesssage::PersistenceObjectManagerUpdateInstanceIdMesssage ()
    : PrismMessage(PersistenceObjectManager::getPrismServiceId(), PERSISTENCE_OBJECT_MANAGER_UPDATE_INSTANCE_ID)
{

}

PersistenceObjectManagerUpdateInstanceIdMesssage::~PersistenceObjectManagerUpdateInstanceIdMesssage ()
{

}

}
