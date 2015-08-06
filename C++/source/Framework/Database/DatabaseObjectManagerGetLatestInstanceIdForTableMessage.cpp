/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerGetLatestInstanceIdForTableMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

DatabaseObjectManagerGetLatestInstanceIdForTableMessage::DatabaseObjectManagerGetLatestInstanceIdForTableMessage (const string &tableName)
    : PrismMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_GET_LATEST_INSTANCE_ID_FOR_TABLE),
      m_tableName (tableName),
      m_latestInstanceId (0)
{
}

DatabaseObjectManagerGetLatestInstanceIdForTableMessage::~DatabaseObjectManagerGetLatestInstanceIdForTableMessage ()
{
}

string DatabaseObjectManagerGetLatestInstanceIdForTableMessage::getTableName () const
{
    return (m_tableName);
}

UI32 DatabaseObjectManagerGetLatestInstanceIdForTableMessage::getLatestInstanceId () const
{
    return (m_latestInstanceId);
}

void DatabaseObjectManagerGetLatestInstanceIdForTableMessage::setLatestInstabceId (const UI32 &latestInstanceId)
{
    m_latestInstanceId = latestInstanceId;
}

}
