/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerExecuteQueryMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

PrismServiceId DatabaseObjectManagerExecuteQueryMessage::m_databaseObjectManagerServiceId;

DatabaseObjectManagerExecuteQueryMessage::DatabaseObjectManagerExecuteQueryMessage (const string &className, WaveObjectManager *pWaveObjectManager, const string &sql, const string &schema)
    : PrismMessage                               (getDatabaseObjectManagerServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_QUERY),
      m_className                                (className),
      m_pWaveObjectManager                       (pWaveObjectManager),
      m_sql                                      (sql),
      m_schema                                   (schema),
      m_loadOneToManyRelationships               (true),
      m_loadCompositions                         (true),
      m_pResults                                 (NULL)
{
    setIsMessageSupportedWhenServiceIsPaused (true);
}

DatabaseObjectManagerExecuteQueryMessage::~DatabaseObjectManagerExecuteQueryMessage ()
{
}

string DatabaseObjectManagerExecuteQueryMessage::getClassName () const
{
    return (m_className);
}

WaveObjectManager *DatabaseObjectManagerExecuteQueryMessage::getPWaveObjectManager () const
{
    return (m_pWaveObjectManager);
}

string DatabaseObjectManagerExecuteQueryMessage::getSql () const
{
    return (m_sql);
}

string DatabaseObjectManagerExecuteQueryMessage::getSchema () const
{
    return (m_schema);
}

vector<string> DatabaseObjectManagerExecuteQueryMessage::getSelectFields () const
{
    return (m_selectFields);
}

void DatabaseObjectManagerExecuteQueryMessage::setSelectFields (const vector<string> &selectFields)
{
    m_selectFields = selectFields;
}

vector<string> DatabaseObjectManagerExecuteQueryMessage::getSelectFieldsInManagedObject () const
{
    return (m_selectFieldsInManagedObject);
}

void DatabaseObjectManagerExecuteQueryMessage::setSelectFieldsInManagedObject (const vector<string> &selectFieldsInManagedObject)
{
    m_selectFieldsInManagedObject = selectFieldsInManagedObject;
}

void DatabaseObjectManagerExecuteQueryMessage::setPResults (vector<WaveManagedObject *> *pResults)
{
    m_pResults = pResults;
}

vector<WaveManagedObject *> *DatabaseObjectManagerExecuteQueryMessage::getPResults () const
{
    return (m_pResults);
}

bool DatabaseObjectManagerExecuteQueryMessage::getLoadOneToManyRelationships () const
{
    return (m_loadOneToManyRelationships);
}

void DatabaseObjectManagerExecuteQueryMessage::setLoadOneToManyRelationships (const bool &loadOneToManyRelationships)
{
    m_loadOneToManyRelationships = loadOneToManyRelationships;
}

bool DatabaseObjectManagerExecuteQueryMessage::getLoadCompositions () const
{
    return (m_loadCompositions);
}

void DatabaseObjectManagerExecuteQueryMessage::setLoadCompositions (const bool loadCompositions)
{
    m_loadCompositions = loadCompositions;
}

PrismServiceId DatabaseObjectManagerExecuteQueryMessage::getDatabaseObjectManagerServiceId ()
{
    return (m_databaseObjectManagerServiceId);
}

void DatabaseObjectManagerExecuteQueryMessage::setDatabaseObjectManagerServiceId (const PrismServiceId &databaseObjectManagerServiceId)
{
    m_databaseObjectManagerServiceId = databaseObjectManagerServiceId;
}


DatabaseObjectManagerDebugChangeQuerySettingsMessage::DatabaseObjectManagerDebugChangeQuerySettingsMessage (const bool &useRecursiveQuery, const UI32 &batchSize)
    : ManagementInterfaceMessage    (DatabaseObjectManager::getClassName (), DATABASE_OBJECT_MANAGER_DEBUG_CHANGE_QUERY_SETTINGS),
      m_useRecursiveQuery           (useRecursiveQuery),
      m_batchSize                   (batchSize)
{
}

DatabaseObjectManagerDebugChangeQuerySettingsMessage::DatabaseObjectManagerDebugChangeQuerySettingsMessage ()
    : ManagementInterfaceMessage    (DatabaseObjectManager::getClassName (), DATABASE_OBJECT_MANAGER_DEBUG_CHANGE_QUERY_SETTINGS),
      m_useRecursiveQuery           (false),
      m_batchSize                   (0)
{
}

DatabaseObjectManagerDebugChangeQuerySettingsMessage::~DatabaseObjectManagerDebugChangeQuerySettingsMessage ()
{
}

void DatabaseObjectManagerDebugChangeQuerySettingsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool (&m_useRecursiveQuery,  "useRecursiveQuery"));
    addSerializableAttribute (new AttributeUI32 (&m_batchSize,          "batchSize"));
}

bool DatabaseObjectManagerDebugChangeQuerySettingsMessage::getUseRecursiveQuery () const
{
    return m_useRecursiveQuery;
}

UI32 DatabaseObjectManagerDebugChangeQuerySettingsMessage::getBatchSize () const
{
    return m_batchSize;
}

}
