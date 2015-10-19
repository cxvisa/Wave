/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerSaveWaveConfigurationMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerSaveWaveConfigurationMessage::PersistenceLocalObjectManagerSaveWaveConfigurationMessage (const bool &isStartupValid)
    : WaveMessage      (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_SAVE_WAVE_CONFIGURATION),
      m_isStartupValid (isStartupValid)
{
}

PersistenceLocalObjectManagerSaveWaveConfigurationMessage::PersistenceLocalObjectManagerSaveWaveConfigurationMessage ()
    : WaveMessage (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_SAVE_WAVE_CONFIGURATION)
{
    m_isStartupValid = false;
}

PersistenceLocalObjectManagerSaveWaveConfigurationMessage::~PersistenceLocalObjectManagerSaveWaveConfigurationMessage ()
{
}

void PersistenceLocalObjectManagerSaveWaveConfigurationMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_isStartupValid, "isStartupValid"));
}

bool PersistenceLocalObjectManagerSaveWaveConfigurationMessage::getIsStartupValid () const
{
    return (m_isStartupValid);
}

void PersistenceLocalObjectManagerSaveWaveConfigurationMessage::setIsStartupValid (const bool &isStartupValid)
{
    m_isStartupValid = isStartupValid;
}

}
