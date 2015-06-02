/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERBACKUPWORKER_H
#define DATABASEOBJECTMANAGERBACKUPWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class DatabaseObjectManagerBackupMessage;

class DatabaseObjectManagerBackupWorker : public WaveWorker
{
    private :
    protected :
    public :
                      DatabaseObjectManagerBackupWorker (WaveObjectManager *pWaveObjectManager);
        virtual      ~DatabaseObjectManagerBackupWorker ();

                void  backupMessageHandler              (DatabaseObjectManagerBackupMessage *pDatabaseObjectManagerBackupMessage);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERBACKUPWORKER_H
