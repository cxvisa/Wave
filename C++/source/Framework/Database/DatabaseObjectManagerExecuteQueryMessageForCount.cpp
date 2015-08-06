/***************************************************************************
 *   Copyright (C) 2008-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerExecuteQueryMessageForCount.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManagerExecuteQueryMessage.h"

namespace WaveNs
{

DatabaseObjectManagerExecuteQueryMessageForCount::DatabaseObjectManagerExecuteQueryMessageForCount (const string &className, WaveObjectManager *pWaveObjectManager, const string &sql)
    : WaveMessage                               (DatabaseObjectManagerExecuteQueryMessage::getDatabaseObjectManagerServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_QUERY_FOR_COUNT),
      m_className                                (className),
      m_pWaveObjectManager                       (pWaveObjectManager),
      m_sql                                      (sql),
      m_count                                    ((UI32) 0)
{
     setIsMessageSupportedWhenServiceIsPaused (true);
}

DatabaseObjectManagerExecuteQueryMessageForCount::~DatabaseObjectManagerExecuteQueryMessageForCount ()
{
}

string DatabaseObjectManagerExecuteQueryMessageForCount::getClassName () const
{
    return (m_className);
}

WaveObjectManager *DatabaseObjectManagerExecuteQueryMessageForCount::getPWaveObjectManager () const
{
    return (m_pWaveObjectManager);
}

string DatabaseObjectManagerExecuteQueryMessageForCount::getSql () const
{
    return (m_sql);
}

void DatabaseObjectManagerExecuteQueryMessageForCount::setCount (const UI32 &count)
{
    m_count = count;
}

UI32 DatabaseObjectManagerExecuteQueryMessageForCount::getCount () const
{
    return (m_count);
}

}
