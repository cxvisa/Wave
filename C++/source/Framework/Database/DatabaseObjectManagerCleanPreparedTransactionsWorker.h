/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERCLEANPREPAREDTRANSACTIONSWORKER_H
#define DATABASEOBJECTMANAGERCLEANPREPAREDTRANSACTIONSWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class DatabaseObjectManager;
class DatabaseObjectManagerCleanPreparedTransactionsMessage;

class DatabaseObjectManagerCleanPreparedTransactionsWorker : public WaveWorker
{
    private :
        void cleanPreparedTransactionsMessageHandler (DatabaseObjectManagerCleanPreparedTransactionsMessage *pDatabaseObjectManagerCleanPreparedTransactionsMessage);

    protected :
    public :
                 DatabaseObjectManagerCleanPreparedTransactionsWorker (DatabaseObjectManager *pDatabaseObjectManager);
        virtual ~DatabaseObjectManagerCleanPreparedTransactionsWorker ();
                 WaveMessage *createMessageInstance                  (const UI32 &operationCode);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERCLEANPREPAREDTRANSACTIONSWORKER_H
