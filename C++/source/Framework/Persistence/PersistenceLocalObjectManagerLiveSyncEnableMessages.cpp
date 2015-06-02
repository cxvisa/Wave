/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerLiveSyncEnableMessages.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------PersistenceLocalObjectManagerGetLiveSyncEnableMessage-------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

PersistenceLocalObjectManagerGetLiveSyncEnableMessage::PersistenceLocalObjectManagerGetLiveSyncEnableMessage ()
    : PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (), PERSISTENCE_GET_LIVE_SYNC_ENABLE), 
      m_isLiveSyncEnabled (false)
{
}

PersistenceLocalObjectManagerGetLiveSyncEnableMessage::~PersistenceLocalObjectManagerGetLiveSyncEnableMessage ()
{
}

void PersistenceLocalObjectManagerGetLiveSyncEnableMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool (&m_isLiveSyncEnabled, "isLiveSyncEnabled"));
}

bool PersistenceLocalObjectManagerGetLiveSyncEnableMessage::getIsLiveSyncEnabled ()
{
    return (m_isLiveSyncEnabled);
}

void PersistenceLocalObjectManagerGetLiveSyncEnableMessage::setIsLiveSyncEnabled (const bool &isLiveSyncEnabled)
{
    m_isLiveSyncEnabled = isLiveSyncEnabled;
}

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------PersistenceLocalObjectManagerSetLiveSyncEnableMessage-------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

PersistenceLocalObjectManagerSetLiveSyncEnableMessage::PersistenceLocalObjectManagerSetLiveSyncEnableMessage ()
    : PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (), PERSISTENCE_SET_LIVE_SYNC_ENABLE), 
      m_isLiveSyncEnabled (false)
{
    setIsMessageSupportedWhenServiceIsPaused (true);
}

PersistenceLocalObjectManagerSetLiveSyncEnableMessage::PersistenceLocalObjectManagerSetLiveSyncEnableMessage (const bool &isLiveSyncEnabled)
    : PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (), PERSISTENCE_SET_LIVE_SYNC_ENABLE), 
      m_isLiveSyncEnabled (isLiveSyncEnabled)
{
    setIsMessageSupportedWhenServiceIsPaused (true);
}

PersistenceLocalObjectManagerSetLiveSyncEnableMessage::~PersistenceLocalObjectManagerSetLiveSyncEnableMessage ()
{
}

void PersistenceLocalObjectManagerSetLiveSyncEnableMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool (&m_isLiveSyncEnabled, "isLiveSyncEnabled"));
}

bool PersistenceLocalObjectManagerSetLiveSyncEnableMessage::getIsLiveSyncEnabled ()
{
    return (m_isLiveSyncEnabled);
}

void PersistenceLocalObjectManagerSetLiveSyncEnableMessage::setIsLiveSyncEnabled (const bool &isLiveSyncEnabled)
{
    m_isLiveSyncEnabled = isLiveSyncEnabled;
}

}
