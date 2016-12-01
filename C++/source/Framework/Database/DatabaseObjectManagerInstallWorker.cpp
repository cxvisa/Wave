/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerInstallWorker.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Database/DatabaseConnection.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace WaveNs
{

bool DatabaseObjectManagerInstallWorker::m_fullInstallRequried = true;

DatabaseObjectManagerInstallWorker::DatabaseObjectManagerInstallWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
}

DatabaseObjectManagerInstallWorker::~DatabaseObjectManagerInstallWorker ()
{
}

void DatabaseObjectManagerInstallWorker::install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    WaveBootReason bootReason = pWaveAsynchronousContextForBootPhases->getBootReason ();

    // In case of persistent boot with default we do not need to install database
    if (WAVE_BOOT_PERSISTENT_WITH_DEFAULT_BOOT == bootReason)
    {
        pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
        pWaveAsynchronousContextForBootPhases->callback ();
        return;
    }

    trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerInstallWorker::install : Entering ...");

    LocationRole thisLocationRole = FrameworkToolKit::getThisLocationRole ();

    if ((LOCATION_PRIMARY != thisLocationRole) && (LOCATION_STAND_ALONE != thisLocationRole))
    {
        pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
        pWaveAsynchronousContextForBootPhases->callback ();
        return;
    }

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerInstallWorker::installValidateStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerInstallWorker::installDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerInstallWorker::installBootDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerInstallWorker::installCreateWaveDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerInstallWorker::installShutdownDatabaseStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerInstallWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&DatabaseObjectManagerInstallWorker::waveLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pWaveAsynchronousContextForBootPhases, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    m_fullInstallRequried = true;

    pWaveLinearSequencerContext->start ();
}

void DatabaseObjectManagerInstallWorker::installValidateStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void DatabaseObjectManagerInstallWorker::installDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerInstallWorker::installDatabaseStep : No support for Persistent Store will be provided.");
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerInstallWorker::installDatabaseStep : Creating repository for persistence ...");

#if 0
    const string   databaseDirectory                 = DatabaseObjectManager::getDatabaseDirectory ();
    const string   databaseInstallCompletionFileName = DatabaseObjectManager::getWaveDatabaseInstallCompletionFileName ();
    const string   completionFilePath                = databaseDirectory + "/" + databaseInstallCompletionFileName;
          ifstream completionFile                      (completionFilePath.c_str (), ios::in);

    if (true == (completionFile.fail ()))
    {
#endif
        //trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installDatabaseStep : Database was never installed.  Initializing Database.");
        trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installDatabaseStep : Initializing Database.");

        int rc = 0;

        rc = system ((string ("rm -rf ") + DatabaseObjectManager::getDatabaseDirectory ()).c_str ());

        if (0 != rc)
        {
            // handle the error.
        }

        rc = system ("rm -rf *.cfg *.pgd");

        if (0 != rc)
        {
            // handle the error.
        }

        // Indicate that initdb output starts below this
        string echoStr = string ("echo \"Executing the initdb command\" >> ") + DatabaseObjectManager::getDatabaseLogFileName ();
        rc = system(echoStr.c_str ());

        if (0 != rc)
        {
            // handle the error.
        }

        string command = string ("initdb -A trust -D ") + DatabaseObjectManager::getDatabaseDirectory () + string (" >> ") + DatabaseObjectManager::getDatabaseLogFileName () + string (" 2>&1");

        // Log the command as well
        echoStr = string("echo \"") + command + string(" \" >> ") + DatabaseObjectManager::getDatabaseLogFileName ();
        rc = system(echoStr.c_str ());

        if (0 != rc)
        {
            // handle the error.
        }

        // Execute the command
        int ret = system(command.c_str ());

        // Log the return status
        trace (TRACE_LEVEL_INFO, string("DatabaseObjectManagerInstallWorker::installDatabaseStep : Initializing Database Completed. Ret:") + ret);

//        PersistenceObjectManager::setSchemaDropRequiredDuringBoot (false);

        m_fullInstallRequried = true;
#if 0
    }
    else
    {
        trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installDatabaseStep : Database was already installed.  Reusing the already initialized Database.");

        system ((string ("pg_ctl -D ") + DatabaseObjectManager::getDatabaseDirectory () + string (" stop")).c_str ());

        system ("rm -rf *.cfg *.pgd");

        completionFile.close ();

        trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installDatabaseStep : Preparation for Reusing Database Completed.");

        PersistenceObjectManager::setSchemaDropRequiredDuringBoot (true);

        m_fullInstallRequried = false;
    }
#endif
    trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerInstallWorker::installDatabaseStep : Done.");

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void DatabaseObjectManagerInstallWorker::installBootDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    if (false == m_fullInstallRequried)
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installBootDatabaseStep : Booting the database to create Wave Database...");

    // Indicate that pg_ctl command output starts below this
    string echoStr = string ("echo \"Executing the pg_ctl start command\" >> ") + DatabaseObjectManager::getDatabaseLogFileName ();
    int rc = system(echoStr.c_str ());

    if (0 != rc)
    {
        // handle the error
    }

    UI8     retries       = 10;
    SI32    status        = -1;
    string  commandString = string ("pg_ctl -D ") + DatabaseObjectManager::getDatabaseDirectory () + DatabaseObjectManager::getDatabaseLogStringForPgctl () + string (" -w -t 120 -o \"--log_line_prefix='%t %a [%e] ' -p ") + DatabaseObjectManager::getDatabasePort () + "\" start >> " + DatabaseObjectManager::getDatabaseLogFileName () + string (" 2>&1");

    // Log the command as well
    echoStr = string("echo \"") + commandString + string(" \" >> ") + DatabaseObjectManager::getDatabaseLogFileName ();
    rc = system(echoStr.c_str ());

    if (0 != rc)
    {
        // handle the error
    }

    // Execute the command
    for (UI8 i = 0; i < retries; i++)
    {
        vector<string>  output;
                        status = FrameworkToolKit::systemCommandOutput (commandString.c_str (), output);

        if (0 == status)
        {
            trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installBootDatabaseStep : Done");
            break;
        }

        /* 
         * Sometimes pg_ctl command returns non-zero but postgres has actually started.
         * So, lets try connecting to DB and confirm if we need to retry 'pg_ctl start' command.
         */

        waveSleep (4);

        bool                isConnectedToDatabse = false;
        DatabaseConnection *pDatabaseConnection  = DatabaseConnection::getInstance (DatabaseObjectManager::getDatabaseName (), DatabaseObjectManager::getDatabasePort ());

        waveAssert (NULL != pDatabaseConnection, __FILE__, __LINE__);

        if (NULL != (pDatabaseConnection->getPConnection ()))
        {
            trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerInstallWorker::installBootDatabaseStep : Already connected to Wave Database. This should not happen as it is just started.");
            waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            isConnectedToDatabse = pDatabaseConnection->connect (120);

            if (false == isConnectedToDatabse)
            {
                trace (TRACE_LEVEL_ERROR, "DatabaseObjectManagerInstallWorker::installBootDatabaseStep : Could not connect to database.");
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installBootDatabaseStep : Connection succeeded even if pg_ctl errored out. Treating postgres has started successfully.");
                DatabaseConnection::deleteInstance ();
                status = 0;
                break;
            }
        }


        trace (TRACE_LEVEL_WARN, "DatabaseObjectManagerInstallWorker::installBootDatabaseStep : failed to start postgres server. -");
        if (0 < output.size())
        {
            tracePrintf (TRACE_LEVEL_WARN, false, true, output[0].c_str());
        }
        waveSleep (4);
    }

    if (0 != status)
    {
        tracePrintf (TRACE_LEVEL_WARN, true, false, string("DatabaseObjectManagerInstallWorker::installBootDatabaseStep : failed to start postgres server after [%s] retries also. Can't move forward. Asserting.").c_str(), retries);
        waveAssert (false, __FILE__, __LINE__);
    }

    // Log the return status
    trace (TRACE_LEVEL_INFO, string("DatabaseObjectManagerInstallWorker::installBootDatabaseStep : ret:") + status);

    waveSleep (5);

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void DatabaseObjectManagerInstallWorker::installCreateWaveDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    if (false == m_fullInstallRequried)
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    const string   databaseDirectory                 = DatabaseObjectManager::getDatabaseDirectory ();
    const string   databaseInstallCompletionFileName = DatabaseObjectManager::getWaveDatabaseInstallCompletionFileName ();
    const string   completionFilePath                = databaseDirectory + "/" + databaseInstallCompletionFileName;
          ofstream completionfileNew;

    trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installCreateWaveDatabaseStep : Creating Wave Database...");

    string commandString = string ("createdb ") + DatabaseObjectManager::getDatabaseName () + " -p " + DatabaseObjectManager::getDatabasePort ();
    int rc = system (commandString.c_str ());

    if (0 != rc)
    {
        // handle the error
    }

    completionfileNew.open (completionFilePath.c_str ());
    completionfileNew.close ();
    completionfileNew.clear ();

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void DatabaseObjectManagerInstallWorker::installShutdownDatabaseStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    if (false == m_fullInstallRequried)
    {
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
        return;
    }

    trace (TRACE_LEVEL_INFO, "DatabaseObjectManagerInstallWorker::installShutdownDatabaseStep : Shutting down the database to create Wave Database...");

    string commandString = string ("pg_ctl -D ") + DatabaseObjectManager::getDatabaseDirectory () + string (" -o \" -p ") + DatabaseObjectManager::getDatabasePort () + "\" stop > /dev/null";
    int rc = system (commandString.c_str ());

    if (0 != rc)
    {
        // handle the error
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
