/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTECOPYSCHEMAWORKER_H
#define DATABASEOBJECTMANAGEREXECUTECOPYSCHEMAWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

typedef enum
{
    ORM_DERIVATIONS_TABLE_TYPE = 0,
    ORM_TABLE_TYPE,
    ORM_AUXILLIARY_TABLE_TYPE,
    ORM_TYPE_END
} OrmTableType;

class WaveObjectManager;

class DatabaseObjectManagerExecuteCopySchemaMessage;

class DatabaseObjectManagerExecuteCopySchemaWorker : public WaveWorker
{
    private :
        virtual PrismMessage *createMessageInstance (const UI32 &operationCode);

    protected :
    public :
                                   DatabaseObjectManagerExecuteCopySchemaWorker (WaveObjectManager *pWaveObjectManager);
        virtual                   ~DatabaseObjectManagerExecuteCopySchemaWorker ();

                void               executeCopySchemaMessageHandler              (DatabaseObjectManagerExecuteCopySchemaMessage *pDatabaseObjectManagerExecuteCopySchemaMessage);


    // Now the data members

    private :
        vector<OrmTableType>     m_tableType;
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGEREXECUTECOPYSCHEMAWORKER_H
