/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerGetDbAccessDetailsMessage.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

DatabaseObjectManagerGetDbAccessDetailsMessage::DatabaseObjectManagerGetDbAccessDetailsMessage ()
    : ManagementInterfaceMessage (DatabaseObjectManager::getClassName (), DATABASE_OBJECT_MANAGER_GET_DB_ACCESS_DETAILS),
      m_port (0)
{
}

DatabaseObjectManagerGetDbAccessDetailsMessage::~DatabaseObjectManagerGetDbAccessDetailsMessage ()
{
}

void DatabaseObjectManagerGetDbAccessDetailsMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

    // This class Specific Attributes below

    addSerializableAttribute (new AttributeString (&m_databaseName, "databaseName"));
    addSerializableAttribute (new AttributeUI32   (&m_port,         "port"));
}

string DatabaseObjectManagerGetDbAccessDetailsMessage::getDatabaseName () const
{
    return (m_databaseName);
}

void DatabaseObjectManagerGetDbAccessDetailsMessage::setDatabaseName (const string &databaseName)
{
    m_databaseName = databaseName;
}

UI32 DatabaseObjectManagerGetDbAccessDetailsMessage::getPort () const
{
    return (m_port);
}

void DatabaseObjectManagerGetDbAccessDetailsMessage::setPort (const UI32 &port)
{
    m_port = port;
}

}
