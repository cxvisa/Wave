/***************************************************************************
*   Copyright (C) 2005-2007 Vidyasagara Guntaka                 			*
*   All rights reserved.													*
*   Author : Sudhakar Jha									*
***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerExecuteCursorCommandMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManagerExecuteQueryMessage.h"

namespace WaveNs
{

DatabaseObjectManagerExecuteCursorCfgCommandMessage::DatabaseObjectManagerExecuteCursorCfgCommandMessage (e_cursorOpCode opCode, string &cursorCommandString, const string &className)
	: WaveMessage          (DatabaseObjectManagerExecuteQueryMessage::getDatabaseObjectManagerServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_CURSOR_CFG_COMMAND),
      m_cursorCommandString	(cursorCommandString),
      m_commandType	        (opCode),
      m_className           (className)
{
}

DatabaseObjectManagerExecuteCursorCfgCommandMessage::~DatabaseObjectManagerExecuteCursorCfgCommandMessage ()
{

}

string DatabaseObjectManagerExecuteCursorCfgCommandMessage::getCursorCfgCommand () const
{
	return (m_cursorCommandString);
}

void   DatabaseObjectManagerExecuteCursorCfgCommandMessage::setCursorCfgCommand (string
&cursorCommandString)
{
	m_cursorCommandString = cursorCommandString;
}


string DatabaseObjectManagerExecuteCursorCfgCommandMessage::getClassName () const
{
    return (m_className);
}

void DatabaseObjectManagerExecuteCursorCfgCommandMessage::setClassName (const string &className)
{
    m_className = className;
}

DatabaseObjectManagerExecuteCursorQueryCommandMessage::DatabaseObjectManagerExecuteCursorQueryCommandMessage 
(string &queryString)
: WaveMessage (DatabaseObjectManagerExecuteQueryMessage::getDatabaseObjectManagerServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_CURSOR_QUERY_COMMAND)
{
	m_cursorQueryString = queryString;
}

DatabaseObjectManagerExecuteCursorQueryCommandMessage::~DatabaseObjectManagerExecuteCursorQueryCommandMessage ()
{

	
}



}
