/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Sudhakar Jha                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerExecuteCursorCommandWorker.h"
#include "Framework/Database/DatabaseObjectManagerExecuteCursorCommandMessage.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseConnection.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Database/DatabaseMultiConnection.h"


namespace WaveNs
{

DatabaseObjectManagerExecuteCursorCommandWorker::DatabaseObjectManagerExecuteCursorCommandWorker (WaveObjectManager *pWaveObjectManager, bool isMultiDatabaseMode)
    : WaveWorker            (pWaveObjectManager),
      m_isMultiDatabaseMode (isMultiDatabaseMode)
{
    addOperationMap (DATABASE_OBJECT_MANAGER_EXECUTE_CURSOR_CFG_COMMAND, reinterpret_cast<WaveMessageHandler> (&DatabaseObjectManagerExecuteCursorCommandWorker::executeCursorCfgCommandMessageHandler));
    addOperationMap (DATABASE_OBJECT_MANAGER_EXECUTE_CURSOR_QUERY_COMMAND, reinterpret_cast<WaveMessageHandler> (&DatabaseObjectManagerExecuteCursorCommandWorker::executeCursorQueryCommandMessageHandler));
}

DatabaseObjectManagerExecuteCursorCommandWorker::~DatabaseObjectManagerExecuteCursorCommandWorker ()
{

}

void DatabaseObjectManagerExecuteCursorCommandWorker::executeCursorCfgCommandMessageHandler (DatabaseObjectManagerExecuteCursorCfgCommandMessage *pDatabaseObjectManagerExecuteCursorCfgCommandMessage)
{

	WaveLinearSequencerStep sequencerSteps[] = 	{	 
		reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerExecuteCursorCommandWorker::executeCursorCfgCommandHandler),
		reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerExecuteCursorCommandWorker::waveLinearSequencerSucceededStep),	 
		reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerExecuteCursorCommandWorker::waveLinearSequencerFailedStep),
	};

	WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pDatabaseObjectManagerExecuteCursorCfgCommandMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));
	pWaveLinearSequencerContext->holdAll ();
	pWaveLinearSequencerContext->start ();

}


void DatabaseObjectManagerExecuteCursorCommandWorker::executeCursorCfgCommandHandler (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{


	DatabaseObjectManagerExecuteCursorCfgCommandMessage *pDatabaseObjectManagerExecuteCursorCfgCommandMessage =
	dynamic_cast<DatabaseObjectManagerExecuteCursorCfgCommandMessage *>(pWaveLinearSequencerContext->getPWaveMessage());

    waveAssert( NULL != pDatabaseObjectManagerExecuteCursorCfgCommandMessage , __FILE__, __LINE__ );

	if ((false == (DatabaseObjectManager::getIsDatabaseEnabled ())) && (false == m_isMultiDatabaseMode))
	{
		trace (TRACE_LEVEL_DEVEL, "DatabaseObjectManagerExecuteCursorCommandWorker::executeCursorCfgCommandHandler : No support for Persistent Store will be provided.");
		pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
		return;
	}

	ResourceId			status				= WAVE_MESSAGE_ERROR;
	PGresult		   *pResult 			= NULL;
	ExecStatusType		databaseStatus		= PGRES_FATAL_ERROR;
	PGconn			   *pConnection 		= getDatabaseServerConnection (pDatabaseObjectManagerExecuteCursorCfgCommandMessage->getClassName ());

	waveAssert (NULL != pConnection, __FILE__, __LINE__);

	pResult = PQexec (pConnection, (pDatabaseObjectManagerExecuteCursorCfgCommandMessage->getCursorCfgCommand ()).c_str ());

	if (NULL == pResult)
	{
		status = WAVE_MESSAGE_ERROR;
	}
	else
	{
		// Keep track of how many commands we executed successfully.  We will execute Vacuum regularly.


		databaseStatus = PQresultStatus (pResult);

		if (PGRES_COMMAND_OK == databaseStatus)
		{
			status = WAVE_MESSAGE_SUCCESS;
		}
		else
		{
			status = WAVE_MESSAGE_ERROR;
			trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerExecuteTransactionWorker::executeTransactionMessageHandler : ERROR in executing the Database Transaction :");
			trace (TRACE_LEVEL_ERROR, string (PQresultErrorMessage (pResult)));
			trace (TRACE_LEVEL_ERROR, "The Errored out SQL was : " + pDatabaseObjectManagerExecuteCursorCfgCommandMessage->getCursorCfgCommand ());
		}

		PQclear (pResult);
	}

	pWaveLinearSequencerContext->executeNextStep (status);

}


/*
  * TBD:- Will implement it in next iteration. 
  * Currently it uses DatabaseObjectManagerExecuteQueryMessage to execute query.
*/

void 
DatabaseObjectManagerExecuteCursorCommandWorker::executeCursorQueryCommandMessageHandler(DatabaseObjectManagerExecuteCursorQueryCommandMessage *pDatabaseObjectManagerExecuteCursorQueryCommandMessage)
{


}

PGconn *DatabaseObjectManagerExecuteCursorCommandWorker::getDatabaseServerConnection (const string &className)
{
    PGconn *pDatabaseServerConnection = NULL;

    if (false == m_isMultiDatabaseMode)
    {
        DatabaseConnection *pDatabaseConnection = DatabaseConnection::getInstance (DatabaseObjectManager::getDatabaseName (), DatabaseObjectManager::getDatabasePort ());

        waveAssert (NULL != pDatabaseConnection, __FILE__, __LINE__);

        pDatabaseServerConnection = pDatabaseConnection->getPConnection ();
    }
    else
    {
        DatabaseMultiConnection *pDatabaseMultiConnection = DatabaseMultiConnection::getInstance ();

        waveAssert (NULL != pDatabaseMultiConnection, __FILE__, __LINE__);

        pDatabaseServerConnection = pDatabaseMultiConnection->getServerConnectionForManagedObject (className);
    }

    return (pDatabaseServerConnection);
}

}
