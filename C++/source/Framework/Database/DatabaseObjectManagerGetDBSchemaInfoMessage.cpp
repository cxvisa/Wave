/***************************************************************************
 *   Copyright (C) 2008-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Mithun B S                                                   *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerGetDBSchemaInfoMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManagerExecuteQueryMessage.h"

namespace WaveNs
{

DatabaseObjectManagerGetDBSchemaInfoMessage::DatabaseObjectManagerGetDBSchemaInfoMessage ()
    : WaveMessage                               (DatabaseObjectManagerExecuteQueryMessage::getDatabaseObjectManagerServiceId (), DATABASE_OBJECT_MANAGER_GET_DB_SCHEMA_INFO)
{
}

DatabaseObjectManagerGetDBSchemaInfoMessage::~DatabaseObjectManagerGetDBSchemaInfoMessage ()
{
}

void DatabaseObjectManagerGetDBSchemaInfoMessage::setDatabaseSchema (const DatabaseSchema &databaseSchema)
{
    m_databaseSchema = databaseSchema;
}

void DatabaseObjectManagerGetDBSchemaInfoMessage::getDatabaseSchema (DatabaseSchema &databaseSchema)
{
    databaseSchema = m_databaseSchema;
}

}
