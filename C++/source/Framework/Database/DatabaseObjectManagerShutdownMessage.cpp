/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerShutdownMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

DatabaseObjectManagerShutdownMessage::DatabaseObjectManagerShutdownMessage ()
    : ManagementInterfaceMessage (DatabaseObjectManager::getClassName (), DATABASE_OBJECT_MANAGER_SHUTDOWN),
      m_isShutdownOnReboot (true)
{
    setIsMessageSupportedWhenServiceIsPaused (true);
}

DatabaseObjectManagerShutdownMessage::DatabaseObjectManagerShutdownMessage (const string &databaseDirectory)
    : ManagementInterfaceMessage (DatabaseObjectManager::getClassName (), DATABASE_OBJECT_MANAGER_SHUTDOWN),
      m_databaseDirectory (databaseDirectory),
      m_isShutdownOnReboot (true)
{
    setIsMessageSupportedWhenServiceIsPaused (true);
}

DatabaseObjectManagerShutdownMessage::DatabaseObjectManagerShutdownMessage (const bool &isShutdownOnReboot)
    : ManagementInterfaceMessage (DatabaseObjectManager::getClassName (), DATABASE_OBJECT_MANAGER_STOP),
      m_isShutdownOnReboot (isShutdownOnReboot)
{
}

DatabaseObjectManagerShutdownMessage::~DatabaseObjectManagerShutdownMessage ()
{
}

void DatabaseObjectManagerShutdownMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_databaseDirectory, "databaseDirectory"));
}

void  DatabaseObjectManagerShutdownMessage::setDatabaseDirectory (const string &databaseDirectory)
{
    m_databaseDirectory = databaseDirectory;
}

string DatabaseObjectManagerShutdownMessage::getDatabaseDirectory () const
{
    return (m_databaseDirectory);
}

void  DatabaseObjectManagerShutdownMessage::setIsShutdownOnReboot (const bool &isShutdownOnReboot)
{
    m_isShutdownOnReboot = isShutdownOnReboot;
}

bool DatabaseObjectManagerShutdownMessage::getIsShutdownOnReboot() const
{
    return (m_isShutdownOnReboot);
}

}
