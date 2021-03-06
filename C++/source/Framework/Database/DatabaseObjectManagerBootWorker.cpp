/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerBootWorker.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseConnection.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "libpq-fe.h"

#include <string>

namespace WaveNs
{

DatabaseObjectManagerBootWorker::DatabaseObjectManagerBootWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
}

DatabaseObjectManagerBootWorker::~DatabaseObjectManagerBootWorker ()
{
}

void DatabaseObjectManagerBootWorker::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerBootWorker::bootValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerBootWorker::bootDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerBootWorker::bootConnectToDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerBootWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerBootWorker::waveLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pWaveAsynchronousContextForBootPhases, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void DatabaseObjectManagerBootWorker::bootValidateStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void DatabaseObjectManagerBootWorker::bootDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        trace (TRACE_LEVEL_DEVEL, "DatabaseObjectManagerBootWorker::bootDatabaseStep : No support for Persistent Store will be provided.");
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    trace (TRACE_LEVEL_DEVEL, "DatabaseObjectManagerBootWorker::bootDatabaseStep : Booting the persistent repository ...");

    DatabaseConnection *pDatabaseConnection = DatabaseConnection::getInstance (DatabaseObjectManager::getDatabaseName (), DatabaseObjectManager::getDatabasePort ());

    waveAssert (NULL != pDatabaseConnection, __FILE__, __LINE__);

    if (NULL != (pDatabaseConnection->getPConnection ()))
    {
        trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootConnectToDatabaseStep : Already connected to Wave Database.  No booting required.");
    }
    else
    {
        int rc = 0;

        rc = system ((string ("pg_ctl -D ") + DatabaseObjectManager::getDatabaseDirectory () + string (" stop")).c_str ());

        if (0 != rc)
        {
            // handle the error.
        }

        rc = system ((string ("chmod 777 ") + DatabaseObjectManager::getDatabaseDirectory () + string ("/postmaster.pid")).c_str ());

        if (0 != rc)
        {
            // handle the error.
        }

        rc = system ((string ("rm -rf ") + DatabaseObjectManager::getDatabaseDirectory () + string ("/postmaster.pid")).c_str ());

        if (0 != rc)
        {
            // handle the error.
        }

        UI8     retries       = 10;
        SI32    status        = -1;  

        // option -w in pg_ctl command returns a non-zero status for command failure. 
        string  commandString = string ("pg_ctl -D ") + DatabaseObjectManager::getDatabaseDirectory () + DatabaseObjectManager::getDatabaseLogStringForPgctl () + string (" -w -o \" -F --shared_buffers=") + DatabaseObjectManager::getDatabaseSharedBuffers () + string (" --max_stack_depth=7680kB --max_prepared_transactions='8'  --max_locks_per_transaction='200' --log_line_prefix='%t %a [%e] ' -p ") + DatabaseObjectManager::getDatabasePort () + "\" start > /dev/null";

        for (UI8 i = 0; i < retries; i++)
        {
            vector<string>  output;
                            status = FrameworkToolKit::systemCommandOutput (commandString.c_str (), output);

            if (0 == status)
            {
                trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootDatabaseStep : Done");
                break;
            }
    
            /* 
             * Sometimes pg_ctl command returns non-zero but postgres has actually started.
             * So, lets try connecting to DB and confirm if we need to retry 'pg_ctl start' command.
             */

            waveSleep (4);

            bool                isConnectedToDatabase = false;
            pDatabaseConnection  = DatabaseConnection::getInstance (DatabaseObjectManager::getDatabaseName (), DatabaseObjectManager::getDatabasePort ());

            waveAssert (NULL != pDatabaseConnection, __FILE__, __LINE__);

            if (NULL != (pDatabaseConnection->getPConnection ()))
            {
                trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerBootWorker::bootDatabaseStep : Already connected to Wave Database. This should not happen as it is just started.");
                waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                isConnectedToDatabase = pDatabaseConnection->connect (120);

                if (false == isConnectedToDatabase)
                {
                    trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerBootWorker::bootDatabaseStep : Could not connect to database.");
                }
                else
                {
                    trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootDatabaseStep : Connection succeeded even if pg_ctl errored out. Treating postgres has started successfully.");
                    DatabaseConnection::deleteInstance ();
                    status = 0;
                    break;
                }
            }


            trace (TRACE_LEVEL_WARN, "DatabaseObjectManagerBootWorker::bootDatabaseStep : failed to start postgres server. -");
            if (0 < output.size())
            {
                tracePrintf (TRACE_LEVEL_WARN, false, true, output[0].c_str());
            }
            waveSleep (4);
        }

        if (0 != status)
        {
            tracePrintf (TRACE_LEVEL_WARN, true, false, string("DatabaseObjectManagerBootWorker::bootDatabaseStep : failed to start postgres server after [%s] retries also. Can't move forward. Asserting.").c_str(), retries);
            waveAssert (false, __FILE__, __LINE__);
        }
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void DatabaseObjectManagerBootWorker::bootConnectToDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        trace (TRACE_LEVEL_DEVEL, "DatabaseObjectManagerBootWorker::bootConnectToDatabaseStep : No support for Persistent Store will be provided.");
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    bool                isConnectedToDatabse = false;
    DatabaseConnection *pDatabaseConnection  = DatabaseConnection::getInstance (DatabaseObjectManager::getDatabaseName (), DatabaseObjectManager::getDatabasePort ());

    waveAssert (NULL != pDatabaseConnection, __FILE__, __LINE__);

    if (NULL != (pDatabaseConnection->getPConnection ()))
    {
        trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootConnectToDatabaseStep : Already connected to Wave Database.");
    }
    else
    {
        isConnectedToDatabse = pDatabaseConnection->connect (120);

        if (false == isConnectedToDatabse)
        {
            trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerBootWorker::bootConnectToDatabaseStep : Could not connect to database.");
            DatabaseObjectManager::setIsDatabaseConnected (false);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootConnectToDatabaseStep : Succesfully connected to Wave Database.");
        }
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;
    trace (TRACE_LEVEL_DEBUG, string("DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep : getIsDatabaseConnected = ") + DatabaseObjectManager::getIsDatabaseConnected () + string(" ,getIsDbRestoreIncomplete = ") + FrameworkToolKit::getIsDbRestoreIncomplete ());

    if ((false ==  DatabaseObjectManager::getIsDatabaseConnected ()) && (true == FrameworkToolKit::getIsDbRestoreIncomplete ()))
    {
        trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep : database has corrupted because of last database restore was incomplete. Need to clean-up and recreate a WaveDatabase.");

        // Delete existing corrupted database and Recreate a fresh WaveDatabase. 
        status = DatabaseObjectManager::createNewWaveDatabase ();
        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep : Could not recreate WaveDatabase");
            status = WAVE_MESSAGE_ERROR;
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {        
            // Connect to the new Database
            bool                isConnectedToDatabase = false;
            DatabaseConnection *pDatabaseConnection   = DatabaseConnection::getInstance (DatabaseObjectManager::getDatabaseName (), DatabaseObjectManager::getDatabasePort ());
            isConnectedToDatabase = pDatabaseConnection->connect (30);
    
            if (false == isConnectedToDatabase)
            {
                trace (TRACE_LEVEL_FATAL, "DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep : Could not connect to database.");
                status = WAVE_MESSAGE_ERROR;
                waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep : Succesfully connected to Wave Database.");
                // Not setting this value here as it is needed in PersistnceOM::boot. Will be set to true there once we are done using it.
                // DatabaseObjectManager::setIsDatabaseConnected (true);
            }
        }
    }
    else 
    {
        if (false == DatabaseObjectManager::getIsDatabaseConnected ())
        {
            trace (TRACE_LEVEL_FATAL, "DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep : Database restore was complete but connection to database could not be established.");
            status = WAVE_MESSAGE_ERROR;
            waveAssert (false, __FILE__, __LINE__);
        }
        else 
        {
            trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerBootWorker::bootReconnectToDatabaseOnInstallIfRequiredStep : connection to the DB is successful."); 
        }
    }

    pWaveLinearSequencerContext->executeNextStep (status);
}

}
