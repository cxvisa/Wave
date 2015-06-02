/**********************************************************************************************
 *  @file : DatabaseObjectManagerCalculateDbCksumWorker.h                                     *
 *   Copyright (C) 2010 Vidyasagara Guntaka                                                   *
 *   All rights reserved.                                                                     *
 *   Description : Declares a class DatabaseObjectManagerCalculateDbCksumWorker.              *
 *                  The handler handles a message DatabaseObjectManagerCalculateDbCksumMessage*
 *                  where it calculates the checksum for local database and reply.            *
 *   Author : Pritee Ghosh                                                                    *
 *   Date   : 02/22/2011                                                                      *
 **********************************************************************************************/

#ifndef DATABASEOBJECTMANAGERCALCULATEDBCKSUMWORKER_H
#define DATABASEOBJECTMANAGERCALCULATEDBCKSUMWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveObjectManager;

class DatabaseObjectManagerCalculateDbCksumMessage;

class DatabaseObjectManagerCalculateDbCksumWorker : public WaveWorker
{
    private :
            virtual PrismMessage  *createMessageInstance                       (const UI32 &operationCode);
    protected :
    public :
                                   DatabaseObjectManagerCalculateDbCksumWorker (WaveObjectManager *pWaveObjectManager);
            virtual               ~DatabaseObjectManagerCalculateDbCksumWorker ();

                    void           calculateDBCksumMessageHandler              (DatabaseObjectManagerCalculateDbCksumMessage *pDatabaseObjectManagerCalculateDbCksumMessage);


    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERCALCULATEDBCKSUMWORKER_H
