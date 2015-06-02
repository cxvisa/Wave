/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Sudhakar Jha                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTECURSORWORKER_H
#define DATABASEOBJECTMANAGEREXECUTECURSORWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "libpq-fe.h"

namespace WaveNs
{

class DatabaseObjectManagerExecuteCursorCfgCommandMessage;
class DatabaseObjectManagerExecuteCursorQueryCommandMessage;

class DatabaseObjectManagerExecuteCursorCommandWorker : public WaveWorker
{
    private :
        PGconn *getDatabaseServerConnection (const string &className);

    protected :
    public :
                      DatabaseObjectManagerExecuteCursorCommandWorker (WaveObjectManager *pWaveObjectManager, bool isMultiDatabaseMode = false);
        virtual      ~DatabaseObjectManagerExecuteCursorCommandWorker ();

                void  executeCursorCfgCommandMessageHandler           (DatabaseObjectManagerExecuteCursorCfgCommandMessage *pDatabaseObjectManagerExecuteCursorCfgCommandMessage);
                void  executeCursorCfgCommandHandler                  (PrismLinearSequencerContext *pPrismLinearSequencerContext);
	
                void  executeCursorQueryCommandMessageHandler         (DatabaseObjectManagerExecuteCursorQueryCommandMessage *pDatabaseObjectManagerExecuteCursorQueryCommandMessage);

    // Now the data members

    private :
        bool m_isMultiDatabaseMode;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERCURSORWORKER_H






