/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerRestoreMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

DatabaseObjectManagerRestoreMessage::DatabaseObjectManagerRestoreMessage (const string &fileToRestoreFrom)
    : PrismMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_RESTORE),
      m_fileToRestoreFrom (fileToRestoreFrom),
      m_restoreSchema (false),
      m_dataOnlyRestore (false),
      m_saveConfiguration (true)
{
}

DatabaseObjectManagerRestoreMessage::~DatabaseObjectManagerRestoreMessage ()
{
}

string DatabaseObjectManagerRestoreMessage::getFileToRestoreFrom () const
{
    return (m_fileToRestoreFrom);
}

bool DatabaseObjectManagerRestoreMessage::getRestoreSchema() const
{
    return (m_restoreSchema);
}

void DatabaseObjectManagerRestoreMessage::setRestoreSchema(const bool isRestoreNeeded)
{
    m_restoreSchema = isRestoreNeeded;
}

bool DatabaseObjectManagerRestoreMessage::getDataOnlyRestore () const
{
    return (m_dataOnlyRestore);
}

void DatabaseObjectManagerRestoreMessage::setDataOnlyRestore (const bool dataOnlyRestore)
{
    m_dataOnlyRestore = dataOnlyRestore;
}

bool DatabaseObjectManagerRestoreMessage::getSaveConfiguration () const
{
    return (m_saveConfiguration);
}

void DatabaseObjectManagerRestoreMessage::setSaveConfiguration (const bool saveConfiguration)
{
    m_saveConfiguration = saveConfiguration;
}

}
