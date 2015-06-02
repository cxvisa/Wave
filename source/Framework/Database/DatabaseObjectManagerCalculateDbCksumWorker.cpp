/**********************************************************************************************
 *  @file : DatabaseObjectManagerCalculateDbCksumWorker.cpp                                   *
 *   Copyright (C) 2010 Vidyasagara Guntaka                                                   *
 *   All rights reserved.                                                                     *
 *   Description : Implements a class DatabaseObjectManagerCalculateDbCksumWorker.            *
 *                  The handler handles a message DatabaseObjectManagerCalculateDbCksumMessage*
 *                  where it calculates the checksum for local database and reply.            *
 *   Author : Pritee Ghosh                                                                    *
 *   Date   : 02/22/2011                                                                      *
 **********************************************************************************************/

#include "Framework/Database/DatabaseObjectManagerCalculateDbCksumWorker.h"
#include "Framework/Database/DatabaseObjectManagerCalculateDbCksumMessage.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseConnection.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

DatabaseObjectManagerCalculateDbCksumWorker::DatabaseObjectManagerCalculateDbCksumWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (DATABASE_OBJECT_MANAGER_CALCULATE_DB_CKSUM, reinterpret_cast<PrismMessageHandler> (&DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler));
}

DatabaseObjectManagerCalculateDbCksumWorker::~DatabaseObjectManagerCalculateDbCksumWorker ()
{
}

PrismMessage *DatabaseObjectManagerCalculateDbCksumWorker::createMessageInstance (const UI32 &operationCode)
{
    PrismMessage *pPrismMessage = NULL;

    switch (operationCode)
    {
        case DATABASE_OBJECT_MANAGER_CALCULATE_DB_CKSUM :
            pPrismMessage = new DatabaseObjectManagerCalculateDbCksumMessage ();
            break;

        default :
            trace (TRACE_LEVEL_FATAL, string ("DatabaseObjectManagerCalculateDbCksumWorker::createMessageInstance : Unknown operation code : ") + operationCode);
            prismAssert (false, __FILE__, __LINE__);
    }

    return (pPrismMessage);
}

void DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler (DatabaseObjectManagerCalculateDbCksumMessage *pDatabaseObjectManagerCalculateDbCksumMessage)
{
    char    cksum [100];
    FILE    *pFile;

    trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : Entering...");

    if (false == (DatabaseObjectManager::getIsDatabaseEnabled ()))
    {
        trace (TRACE_LEVEL_DEVEL, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler: No support for Persistent Store will be provided.");
        pDatabaseObjectManagerCalculateDbCksumMessage->setCompletionStatus (WAVE_MESSAGE_ERROR);
        reply (pDatabaseObjectManagerCalculateDbCksumMessage);
        return;
    }

    trace (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : Calculating Database checksum...");

    string commandString = string (" pg_dump --schema=WaveCurrent --format=p") + string (" --port=") + DatabaseObjectManager::getDatabasePort () + string (" ") + DatabaseObjectManager::getDatabaseName () + string (" | /bin/sort | /usr/bin/md5sum | /usr/bin/cut -d ' ' -f 1 ");

    tracePrintf (TRACE_LEVEL_INFO, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : commandString= %s", commandString.c_str ());
    pFile = popen (commandString.c_str (), "r");

    if (pFile == NULL)
    {
        trace (TRACE_LEVEL_ERROR, string("DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler: Failed to calculate the cksum for database") + commandString.c_str ());
        pDatabaseObjectManagerCalculateDbCksumMessage->setCompletionStatus (WAVE_MESSAGE_ERROR);
        reply (pDatabaseObjectManagerCalculateDbCksumMessage);
        return;
    }

    fgets (cksum, 100, pFile);

    fclose (pFile);
    tracePrintf (TRACE_LEVEL_DEBUG, "DatabaseObjectManagerCalculateDbCksumWorker::calculateDBCksumMessageHandler : cksum = %s", cksum); 


    pDatabaseObjectManagerCalculateDbCksumMessage->setDbCksumForNode (cksum);
    pDatabaseObjectManagerCalculateDbCksumMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pDatabaseObjectManagerCalculateDbCksumMessage);
}

}
