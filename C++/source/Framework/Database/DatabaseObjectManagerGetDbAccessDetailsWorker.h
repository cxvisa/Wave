/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERGETDBACCESSDETAILSWORKER_H
#define DATABASEOBJECTMANAGERGETDBACCESSDETAILSWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class DatabaseObjectManagerGetDbAccessDetailsMessage;

class DatabaseObjectManagerGetDbAccessDetailsWorker : public WaveWorker
{
    private :
        virtual PrismMessage *createMessageInstance            (const UI32 &operationCode);
                void          getDbAccessDetailsMessageHandler (DatabaseObjectManagerGetDbAccessDetailsMessage *pDatabaseObjectManagerGetDbAccessDetailsMessage);

    protected :
    public :
                        DatabaseObjectManagerGetDbAccessDetailsWorker (WaveObjectManager *pWaveObjectManager);
        virtual        ~DatabaseObjectManagerGetDbAccessDetailsWorker ();
        static void     getDbAccessDetailsMessageStaticHandler (DatabaseObjectManagerGetDbAccessDetailsMessage *pDatabaseObjectManagerGetDbAccessDetailsMessage);

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERGETDBACCESSDETAILSWORKER_H
