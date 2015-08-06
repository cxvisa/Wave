/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerExecuteTransactionMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Attributes/AttributeResourceId.h"

namespace WaveNs
{

PersistenceObjectManagerExecuteTransactionMessage::PersistenceObjectManagerExecuteTransactionMessage (const string &sql)
    : WaveMessage (PersistenceObjectManager::getWaveServiceId (), PERSISTENCE_OBNJECT_MANAGER_EXECUTE_TRANSACTION),
      m_sql (sql)
{
}

PersistenceObjectManagerExecuteTransactionMessage::PersistenceObjectManagerExecuteTransactionMessage ()
    : WaveMessage (PersistenceObjectManager::getWaveServiceId (), PERSISTENCE_OBNJECT_MANAGER_EXECUTE_TRANSACTION)
{
}

PersistenceObjectManagerExecuteTransactionMessage::~PersistenceObjectManagerExecuteTransactionMessage ()
{
}

void PersistenceObjectManagerExecuteTransactionMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_sql, "sql"));

    addSerializableAttribute (new AttributeStringVector     (&m_configNamesForInsert,             "configNamesForInsert"));
    addSerializableAttribute (new AttributeStringVector     (&m_configValuesForInsert,            "configValuesForInsert"));
    addSerializableAttribute (new AttributeResourceIdVector (&m_configTypesForInsert,             "configTypesForInsert"));

    addSerializableAttribute (new AttributeStringVector     (&m_configNamesForUpdate,             "configNamesForUpdate"));
    addSerializableAttribute (new AttributeStringVector     (&m_configValuesForUpdate,            "configValuesForUpdate"));
    addSerializableAttribute (new AttributeResourceIdVector (&m_configTypesForUpdate,             "configTypesForUpdate"));
}

const string &PersistenceObjectManagerExecuteTransactionMessage::getSql () const
{
    return (m_sql);
}

void PersistenceObjectManagerExecuteTransactionMessage::setSql (const string &sql)
{
    m_sql = sql;
}

void PersistenceObjectManagerExecuteTransactionMessage::setConfigNamesForInsert (const vector<string> &configNamesForInsert)
{
    m_configNamesForInsert = configNamesForInsert;
}

vector<string> PersistenceObjectManagerExecuteTransactionMessage::getConfigNamesForInsert () const
{
    return (m_configNamesForInsert);
}

void PersistenceObjectManagerExecuteTransactionMessage::setConfigValuesForInsert (const vector<string> &configValuesForInsert)
{
    m_configValuesForInsert = configValuesForInsert;
}

vector<string> PersistenceObjectManagerExecuteTransactionMessage::getConfigValuesForInsert () const
{
    return (m_configValuesForInsert);
}

void PersistenceObjectManagerExecuteTransactionMessage::setConfigTypesForInsert (const vector<ResourceId> &configTypesForInsert)
{
    m_configTypesForInsert = configTypesForInsert;
}

vector<ResourceId> PersistenceObjectManagerExecuteTransactionMessage::getConfigTypesForInsert () const
{
    return (m_configTypesForInsert);
}

void PersistenceObjectManagerExecuteTransactionMessage::setConfigNamesForUpdate (const vector<string> &configNamesForUpdate)
{
    m_configNamesForUpdate = configNamesForUpdate;
}

vector<string> PersistenceObjectManagerExecuteTransactionMessage::getConfigNamesForUpdate () const
{
    return (m_configNamesForUpdate);
}

void PersistenceObjectManagerExecuteTransactionMessage::setConfigValuesForUpdate (const vector<string> &configValuesForUpdate)
{
    m_configValuesForUpdate = configValuesForUpdate;
}

vector<string> PersistenceObjectManagerExecuteTransactionMessage::getConfigValuesForUpdate () const
{
    return (m_configValuesForUpdate);
}

void PersistenceObjectManagerExecuteTransactionMessage::setConfigTypesForUpdate (const vector<ResourceId> &configTypesForUpdate)
{
    m_configTypesForUpdate = configTypesForUpdate;
}

vector<ResourceId> PersistenceObjectManagerExecuteTransactionMessage::getConfigTypesForUpdate () const
{
    return (m_configTypesForUpdate);
}

}
