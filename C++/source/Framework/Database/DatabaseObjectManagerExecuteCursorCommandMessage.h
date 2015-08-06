/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Sudhakar Jha                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTECURSORCOMMANDMESSAGE_H
#define DATABASEOBJECTMANAGEREXECUTECURSORCOMMANDMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

enum e_cursorOpCode
{
	CURSOR_DECLARE,
	CURSOR_FETCH,
	CURSOR_MOVE,
	CURSOR_CLOSE
};


class DatabaseObjectManagerExecuteCursorCfgCommandMessage : public WaveMessage
{
    private :
    protected :
    public :
                        DatabaseObjectManagerExecuteCursorCfgCommandMessage (e_cursorOpCode opCode, string &cursorCommandString, const string &className);
        virtual        ~DatabaseObjectManagerExecuteCursorCfgCommandMessage ();

                string  getCursorCfgCommand                                 () const;
                void    setCursorCfgCommand                                 (string &cursorCommandString);

                string  getClassName                                        () const;
                void    setClassName                                        (const string &className);

    // Now the data members

    private :
        string         m_cursorCommandString;
	    e_cursorOpCode m_commandType;
        string         m_className;

    protected :
    public :
};


class DatabaseObjectManagerExecuteCursorQueryCommandMessage : public WaveMessage
{
	private :
	protected :
	public :
                 DatabaseObjectManagerExecuteCursorQueryCommandMessage (string &queryString);
		virtual ~DatabaseObjectManagerExecuteCursorQueryCommandMessage ();

	// Now the data members

	private :
		string m_cursorQueryString;

	protected :
	public :
};


}

#endif // DATABASEOBJECTMANAGEREXECUTECURSORCOMMANDMESSAGE_H

