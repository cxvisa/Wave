/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerExecuteTransactionMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

DatabaseObjectManagerExecuteTransactionMessage::DatabaseObjectManagerExecuteTransactionMessage (const string &sql)
    : WaveMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_TRANSACTION),
      m_sql (sql),
      m_isCommit (false),
      m_isPrepare (false)
{
}

DatabaseObjectManagerExecuteTransactionMessage::DatabaseObjectManagerExecuteTransactionMessage ()
    : WaveMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_TRANSACTION),
      m_isCommit (false),
      m_isPrepare (false)
{
}

DatabaseObjectManagerExecuteTransactionMessage::~DatabaseObjectManagerExecuteTransactionMessage ()
{
}

void DatabaseObjectManagerExecuteTransactionMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_sql,         "sql"));
     addSerializableAttribute (new AttributeBool   (&m_isCommit,    "isCommit"));
     addSerializableAttribute (new AttributeBool   (&m_isPrepare,   "isPrepare"));
}

const string &DatabaseObjectManagerExecuteTransactionMessage::getSql () const
{
    return (m_sql);
}

void DatabaseObjectManagerExecuteTransactionMessage::setSql (const string &sql)
{
    m_sql = sql;
}

bool DatabaseObjectManagerExecuteTransactionMessage::getIsCommit () const
{
    return (m_isCommit);
}

void DatabaseObjectManagerExecuteTransactionMessage::setIsCommit (const bool &isCommit)
{
    m_isCommit = isCommit;
}

bool DatabaseObjectManagerExecuteTransactionMessage::getIsPrepare () const
{
    return (m_isPrepare);
}

void DatabaseObjectManagerExecuteTransactionMessage::setIsPrepare (const bool &isPrepare)
{
    m_isPrepare = isPrepare;
}

}
