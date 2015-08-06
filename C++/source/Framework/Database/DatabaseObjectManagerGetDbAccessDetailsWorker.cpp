/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerGetDbAccessDetailsWorker.h"
#include "Framework/Database/DatabaseObjectManagerGetDbAccessDetailsMessage.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManager.h"

namespace WaveNs
{

DatabaseObjectManagerGetDbAccessDetailsWorker::DatabaseObjectManagerGetDbAccessDetailsWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (DATABASE_OBJECT_MANAGER_GET_DB_ACCESS_DETAILS, reinterpret_cast<WaveMessageHandler> (&DatabaseObjectManagerGetDbAccessDetailsWorker::getDbAccessDetailsMessageHandler));
    addServiceIndependentOperationMap (DATABASE_OBJECT_MANAGER_GET_DB_ACCESS_DETAILS, reinterpret_cast<ManagementInterfaceServiceIndependentMessageHandler> (&DatabaseObjectManagerGetDbAccessDetailsWorker::getDbAccessDetailsMessageStaticHandler));
}

DatabaseObjectManagerGetDbAccessDetailsWorker::~DatabaseObjectManagerGetDbAccessDetailsWorker ()
{
}

WaveMessage *DatabaseObjectManagerGetDbAccessDetailsWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case DATABASE_OBJECT_MANAGER_GET_DB_ACCESS_DETAILS :
            pWaveMessage = new DatabaseObjectManagerGetDbAccessDetailsMessage ();
            break;

        default :
            trace (TRACE_LEVEL_FATAL, string ("DatabaseObjectManagerGetDbAccessDetailsWorker::createMessageInstance : Unknown operation code : ") + operationCode);
            waveAssert (false, __FILE__, __LINE__);
            break;
    }

    return (pWaveMessage);
}

void DatabaseObjectManagerGetDbAccessDetailsWorker::getDbAccessDetailsMessageHandler (DatabaseObjectManagerGetDbAccessDetailsMessage *pDatabaseObjectManagerGetDbAccessDetailsMessage)
{
    DatabaseObjectManagerGetDbAccessDetailsWorker::getDbAccessDetailsMessageStaticHandler (pDatabaseObjectManagerGetDbAccessDetailsMessage);
    reply (pDatabaseObjectManagerGetDbAccessDetailsMessage);
}

void DatabaseObjectManagerGetDbAccessDetailsWorker::getDbAccessDetailsMessageStaticHandler (DatabaseObjectManagerGetDbAccessDetailsMessage *pDatabaseObjectManagerGetDbAccessDetailsMessage)
{
    pDatabaseObjectManagerGetDbAccessDetailsMessage->setDatabaseName (DatabaseObjectManager::getDatabaseName ());
    pDatabaseObjectManagerGetDbAccessDetailsMessage->setPort         (DatabaseObjectManager::getDatabasePort ());

    pDatabaseObjectManagerGetDbAccessDetailsMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
}

}
