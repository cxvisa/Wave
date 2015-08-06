/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERSHUTDOWNWORKER_H
#define DATABASEOBJECTMANAGERSHUTDOWNWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class DatabaseObjectManagerShutdownMessage;

class DatabaseObjectManagerShutdownWorker : public WaveWorker
{
    private :
        virtual     WaveMessage   *createMessageInstance               (const UI32 &operationCode);

    protected :
    public :
                                    DatabaseObjectManagerShutdownWorker (WaveObjectManager *pWaveObjectManager);
        virtual                    ~DatabaseObjectManagerShutdownWorker ();
                
        void                        shutdownMessageHandler              (DatabaseObjectManagerShutdownMessage *pDatabaseObjectManagerShutdownMessage);
        void                        stopMessageHandler                  (DatabaseObjectManagerShutdownMessage *pDatabaseObjectManagerShutdownMessage);

    // Now the data members

    private :

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERBOOTWORKER_H
