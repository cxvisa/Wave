/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerEnableTransactionMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerEnableTransactionMessage::PersistenceLocalObjectManagerEnableTransactionMessage ()
    : WaveMessage (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_LOCAL_OBJECT_MANAGER_ENABLE_TRANSACTION)
{
}

PersistenceLocalObjectManagerEnableTransactionMessage::~PersistenceLocalObjectManagerEnableTransactionMessage ()
{
}

void PersistenceLocalObjectManagerEnableTransactionMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

}
