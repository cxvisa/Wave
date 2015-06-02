/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREMPTYWORKER_H
#define DATABASEOBJECTMANAGEREMPTYWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class DatabaseObjectManagerEmptyMessage;
class DatabaseObjectManagerEmptyDatabaseParameterConfigureMessage;

class DatabaseObjectManagerEmptyWorker : public WaveWorker
{
    private :
        virtual PrismMessage   *createMessageInstance                        (const UI32 &operationCode);
    protected :
    public :
                               DatabaseObjectManagerEmptyWorker              (WaveObjectManager *pWaveObjectManager);
        virtual               ~DatabaseObjectManagerEmptyWorker              ();

                void           emptyMessageHandler                           (DatabaseObjectManagerEmptyMessage *pDatabaseObjectManagerEmptyMessage);
                void           emptyDatabaseParameterConfigureMessageHandler (DatabaseObjectManagerEmptyDatabaseParameterConfigureMessage *pDatabaseObjectManagerEmptyDatabaseParameterConfigureMessage);
    // Now the data members

    private :
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGEREMPTYWORKER_H
