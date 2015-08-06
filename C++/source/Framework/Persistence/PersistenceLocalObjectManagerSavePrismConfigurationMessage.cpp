/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerSavePrismConfigurationMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerSavePrismConfigurationMessage::PersistenceLocalObjectManagerSavePrismConfigurationMessage (const bool &isStartupValid)
    : WaveMessage      (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_SAVE_PRISM_CONFIGURATION),
      m_isStartupValid (isStartupValid)
{
}

PersistenceLocalObjectManagerSavePrismConfigurationMessage::PersistenceLocalObjectManagerSavePrismConfigurationMessage ()
    : WaveMessage (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_SAVE_PRISM_CONFIGURATION)
{
    m_isStartupValid = false;
}

PersistenceLocalObjectManagerSavePrismConfigurationMessage::~PersistenceLocalObjectManagerSavePrismConfigurationMessage ()
{
}

void PersistenceLocalObjectManagerSavePrismConfigurationMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_isStartupValid, "isStartupValid"));
}

bool PersistenceLocalObjectManagerSavePrismConfigurationMessage::getIsStartupValid () const
{
    return (m_isStartupValid);
}

void PersistenceLocalObjectManagerSavePrismConfigurationMessage::setIsStartupValid (const bool &isStartupValid)
{
    m_isStartupValid = isStartupValid;
}

}
