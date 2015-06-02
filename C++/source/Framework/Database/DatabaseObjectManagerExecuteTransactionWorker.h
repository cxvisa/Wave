/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTETRANSACTIONWORKER_H
#define DATABASEOBJECTMANAGEREXECUTETRANSACTIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveObjectManager;
class DatabaseObjectManagerExecuteTransactionMessage;
class WaveAsynchronousContextForDebugInformation;

class DatabaseObjectManagerExecuteTransactionWorker : public WaveWorker
{
    private :
        virtual PrismMessage   *createMessageInstance                           (const UI32 &operationCode);
        virtual void            getDebugInformation                             (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);
        virtual void            resetDebugInformation                           (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);

    protected :
    public :
                                DatabaseObjectManagerExecuteTransactionWorker   (WaveObjectManager *pWaveObjectManager);
        virtual                ~DatabaseObjectManagerExecuteTransactionWorker   ();

               void             executeTransactionMessageHandler                (DatabaseObjectManagerExecuteTransactionMessage *pDatabaseObjectManagerExecuteTransactionMessage);

        static ResourceId       printTransactionStats                           (UI32 argc, vector<string> argv);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGEREXECUTETRANSACTIONWORKER_H
