/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERGETLATESTINSTANCEIDFORTABLEWORKER_H
#define DATABASEOBJECTMANAGERGETLATESTINSTANCEIDFORTABLEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class DatabaseObjectManagerGetLatestInstanceIdForTableMessage;

class DatabaseObjectManagerGetLatestInstanceIdForTableWorker : public WaveWorker
{
    private :
        void getLatestInstanceIdForTableMessageHandler (DatabaseObjectManagerGetLatestInstanceIdForTableMessage *pDatabaseObjectManagerGetLatestInstanceIdForTableMessage);

    protected :
    public :
         DatabaseObjectManagerGetLatestInstanceIdForTableWorker (WaveObjectManager *pWaveObjectManager);
        ~DatabaseObjectManagerGetLatestInstanceIdForTableWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERGETLATESTINSTANCEIDFORTABLEWORKER_H
