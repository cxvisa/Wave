/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERRESTOREWORKER_H
#define DATABASEOBJECTMANAGERRESTOREWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class DatabaseObjectManagerRestoreMessage;

class DatabaseObjectManagerRestoreWorker : public WaveWorker
{
    private :
    protected :
    public :
                      DatabaseObjectManagerRestoreWorker (WaveObjectManager *pWaveObjectManager);
        virtual      ~DatabaseObjectManagerRestoreWorker ();

                void  restoreMessageHandler              (DatabaseObjectManagerRestoreMessage *pDatabaseObjectManagerRestoreMessage);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERRESTOREWORKER_H
