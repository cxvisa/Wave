/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerCleanPreparedTransactionsWorker.h"
#include "Framework/Database/DatabaseObjectManagerCleanPreparedTransactionsMessage.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseConnection.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

DatabaseObjectManagerCleanPreparedTransactionsWorker::DatabaseObjectManagerCleanPreparedTransactionsWorker (DatabaseObjectManager *pDatabaseObjectManager)
    : WaveWorker (pDatabaseObjectManager)
{
    addOperationMap (DATABASE_OBJECT_MANAGER_CLEAN_PREPARED_TRANSACTIONS, reinterpret_cast<WaveMessageHandler> (&DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler));
}

DatabaseObjectManagerCleanPreparedTransactionsWorker::~DatabaseObjectManagerCleanPreparedTransactionsWorker ()
{
}

WaveMessage *DatabaseObjectManagerCleanPreparedTransactionsWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case DATABASE_OBJECT_MANAGER_CLEAN_PREPARED_TRANSACTIONS:
            pWaveMessage = new DatabaseObjectManagerCleanPreparedTransactionsMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler (DatabaseObjectManagerCleanPreparedTransactionsMessage *pDatabaseObjectManagerCleanPreparedTransactionsMessage)
{
    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        trace (TRACE_LEVEL_DEVEL, "DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler : No support for Persistent Store will be provided.");
        pDatabaseObjectManagerCleanPreparedTransactionsMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
        reply (pDatabaseObjectManagerCleanPreparedTransactionsMessage);
        return;
    }

    ResourceId          status                       = WAVE_MESSAGE_ERROR;
    DatabaseConnection *pDatabaseConnection          = DatabaseConnection::getInstance (DatabaseObjectManager::getDatabaseName (), DatabaseObjectManager::getDatabasePort ());
    PGresult           *pResult                      = NULL;
    ExecStatusType      databaseStatus               = PGRES_FATAL_ERROR;
    PGconn             *pConnection                  = pDatabaseConnection->getPConnection ();
    string              queryPreparedTransactionsSql = "SELECT gid FROM pg_prepared_xacts;";

    prismAssert (NULL != pConnection, __FILE__, __LINE__);

    pResult = PQexec (pDatabaseConnection->getPConnection (), queryPreparedTransactionsSql.c_str ());

    if (NULL == pResult)
    {
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        databaseStatus = PQresultStatus (pResult);

        if (PGRES_TUPLES_OK == databaseStatus)
        {
            status = WAVE_MESSAGE_SUCCESS;

            trace (TRACE_LEVEL_DEBUG, string ("DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler : Got ") + PQntuples (pResult) + string (" results."));

            UI32   numberOfResults               = PQntuples (pResult);
            UI32   row                           = 0;
            string cleanPreparedTransactionsSql;

            if (0 == numberOfResults)
            {
                trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler : There are NO Prepared Transactions to be cleaned.");
            }
            else
            {
                UI32 column     = PQfnumber (pResult, "gid");
                bool anyFailure = false;

                for (row = 0; row < numberOfResults; row++)
                {
                    char *pValue = PQgetvalue (pResult, row, column);

                    cleanPreparedTransactionsSql = string ("ROLLBACK PREPARED \'") + pValue + string ("\';\n");

                    trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler : SQL To Clean Prepared Transactions :\n    " + cleanPreparedTransactionsSql);

                    PGresult   *pResult1 = NULL;
                    ResourceId  status1  = WAVE_MESSAGE_SUCCESS;

                    pResult1 = PQexec (pDatabaseConnection->getPConnection (), cleanPreparedTransactionsSql.c_str ());

                    if (NULL == pResult1)
                    {
                        status1    = WAVE_MESSAGE_ERROR;
                        anyFailure = true;
                    }
                    else
                    {
                        databaseStatus = PQresultStatus (pResult1);

                        if (PGRES_COMMAND_OK == databaseStatus)
                        {
                            status1 = WAVE_MESSAGE_SUCCESS;
                        }
                        else
                        {
                            status1    = WAVE_MESSAGE_ERROR;
                            anyFailure = true;
                            string errorMessage = string (PQresultErrorMessage (pResult1));        


                            trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler : ERROR in executing the Database Transaction :" + errorMessage);
                            //trace (TRACE_LEVEL_ERROR, string (PQresultErrorMessage (pResult1)));
                            trace (TRACE_LEVEL_ERROR, "The Errored out SQL was : " + cleanPreparedTransactionsSql);
                            trace (TRACE_LEVEL_ERROR, "Status                  : " + FrameworkToolKit::localize (status1));
                            
                            DatabaseObjectManager::handleIfDBCorruption (errorMessage, pResult1);
                        }

                        PQclear (pResult1);
                    }
                }

                if (true == anyFailure)
                {
                    trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler : Some OR All of the Prepared Transactions Could NOT be cleaned.");
                    status = WAVE_MESSAGE_ERROR;
                }
            }
        }
        else
        {
            status              = WAVE_MESSAGE_ERROR;
            string errorMessage = string (PQresultErrorMessage (pResult));
            trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerCleanPreparedTransactionsWorker::cleanPreparedTransactionsMessageHandler : ERROR in executing the Database Transaction :" + errorMessage);
            //trace (TRACE_LEVEL_ERROR, string (PQresultErrorMessage (pResult)));
            trace (TRACE_LEVEL_ERROR, "The Errored out SQL was : " + queryPreparedTransactionsSql);

            DatabaseObjectManager::handleIfDBCorruption (errorMessage, pResult);
        }

        PQclear (pResult);
    }

    pDatabaseObjectManagerCleanPreparedTransactionsMessage->setCompletionStatus (status);
    reply (pDatabaseObjectManagerCleanPreparedTransactionsMessage);
}

}
