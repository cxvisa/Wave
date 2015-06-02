/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerBackupMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

DatabaseObjectManagerBackupMessage::DatabaseObjectManagerBackupMessage (const string &backupFileName, const bool &pauseTheService)
    : PrismMessage (DatabaseObjectManager::getPrismServiceId (), DATABASE_OBJECT_MANAGER_BACKUP),
      m_backupFileName (backupFileName),
      m_pauseTheService (pauseTheService),
      m_backupAllSchemas (false),
      m_dataOnlyBackup (false)
{
}

DatabaseObjectManagerBackupMessage::~DatabaseObjectManagerBackupMessage ()
{
}

string DatabaseObjectManagerBackupMessage::getBackupFileName () const
{
    return (m_backupFileName);
}

void DatabaseObjectManagerBackupMessage::setBackupFileName (const string &backupFileName)
{
    m_backupFileName = backupFileName;
}

bool DatabaseObjectManagerBackupMessage::getPauseTheService () const
{
    return (m_pauseTheService);
}

void DatabaseObjectManagerBackupMessage::setBackupAllSchema (const bool isNeeded)
{
    m_backupAllSchemas = isNeeded;
}

bool DatabaseObjectManagerBackupMessage::getBackupAllSchema() const
{
    return (m_backupAllSchemas);
}

bool DatabaseObjectManagerBackupMessage::getDataOnlyBackup () const
{
    return (m_dataOnlyBackup);
}

void DatabaseObjectManagerBackupMessage::setDataOnlyBackup (const bool dataOnlyBackup)
{
    m_dataOnlyBackup = dataOnlyBackup;
}

}
