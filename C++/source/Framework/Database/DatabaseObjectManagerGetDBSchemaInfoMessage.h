/***************************************************************************
 *   Copyright (C) 2008-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Mithun B S                                                   *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERGETDBSCHEMAINFOMESSAGE_H
#define DATABASEOBJECTMANAGERGETDBSCHEMAINFOMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/ObjectRelationalMapping/DatabaseSchema.h"

using namespace std;

namespace WaveNs
{

class WaveManagedObject;
class WaveObjectManager;

class DatabaseObjectManagerGetDBSchemaInfoMessage : public WaveMessage
{
    private :
    protected :
    public :
                                             DatabaseObjectManagerGetDBSchemaInfoMessage ();
        virtual                             ~DatabaseObjectManagerGetDBSchemaInfoMessage ();

                void                         getDatabaseSchema                              (DatabaseSchema &databaseSchema);
                void                         setDatabaseSchema                              (const DatabaseSchema &databaseSchema);
    // Now the data members

    private :
        DatabaseSchema m_databaseSchema;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERGETDBSCHEMAINFOMESSAGE_H
