/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerPushConfigToKernelMessaage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerPushConfigToKernelMessaage::PersistenceLocalObjectManagerPushConfigToKernelMessaage (const string &globalConfigs)
    : PrismMessage (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_PUSH_CONFIG_TO_KERNEL),
      m_globalConfigs (globalConfigs)
{
}

PersistenceLocalObjectManagerPushConfigToKernelMessaage::PersistenceLocalObjectManagerPushConfigToKernelMessaage()
    : PrismMessage (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_PUSH_CONFIG_TO_KERNEL)
{
}

PersistenceLocalObjectManagerPushConfigToKernelMessaage::~PersistenceLocalObjectManagerPushConfigToKernelMessaage ()
{
}

void PersistenceLocalObjectManagerPushConfigToKernelMessaage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_globalConfigs, "globalConfigs"));
}

string PersistenceLocalObjectManagerPushConfigToKernelMessaage::getGlobalConfigs () const
{
    return (m_globalConfigs);
}

void PersistenceLocalObjectManagerPushConfigToKernelMessaage::setGlobalConfigs (const string &globalConfigs)
{
    m_globalConfigs = globalConfigs;
}

}
