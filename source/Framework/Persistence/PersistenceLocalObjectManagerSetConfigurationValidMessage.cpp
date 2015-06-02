/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Anil ChannaveeraSetty                                        *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerSetConfigurationValidMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerSetConfigurationValidMessage::PersistenceLocalObjectManagerSetConfigurationValidMessage (const bool &validity, const string &schemaFileName)
    : ManagementInterfaceMessage (PersistenceLocalObjectManager::getServiceName (), PERSISTENCE_SET_CONFIGURATION_VALID),
     m_isConfigurationValid (validity),
     m_schemaFile (schemaFileName)
{
}

PersistenceLocalObjectManagerSetConfigurationValidMessage::PersistenceLocalObjectManagerSetConfigurationValidMessage ()
    : ManagementInterfaceMessage (PersistenceLocalObjectManager::getServiceName (), PERSISTENCE_SET_CONFIGURATION_VALID)
{
}

PersistenceLocalObjectManagerSetConfigurationValidMessage::~PersistenceLocalObjectManagerSetConfigurationValidMessage ()
{
}

void PersistenceLocalObjectManagerSetConfigurationValidMessage::setupAttributesForSerialization ()
{   
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool   (&m_isConfigurationValid,    "isConfigurationValid"));
     addSerializableAttribute (new AttributeString (&m_schemaFile,              "schemaFile"));
}

bool PersistenceLocalObjectManagerSetConfigurationValidMessage::getConfigurationValidity () const
{   
    return (m_isConfigurationValid);
}

void PersistenceLocalObjectManagerSetConfigurationValidMessage::setConfigurationValidity (const bool &validity)
{   
    m_isConfigurationValid = validity;
}

string PersistenceLocalObjectManagerSetConfigurationValidMessage::getSchemaFile () const
{
    return (m_schemaFile);
}

void PersistenceLocalObjectManagerSetConfigurationValidMessage::setSchemaFile (const string &schemaFileName)
{
    m_schemaFile = schemaFileName;
}

}
