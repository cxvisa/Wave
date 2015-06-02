/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERGETLATESTINSTANCEIDFORTABLEMESSAGE_H
#define DATABASEOBJECTMANAGERGETLATESTINSTANCEIDFORTABLEMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class DatabaseObjectManagerGetLatestInstanceIdForTableMessage : public PrismMessage
{
    private :
    protected :
    public :
                        DatabaseObjectManagerGetLatestInstanceIdForTableMessage (const string &tableName);
        virtual        ~DatabaseObjectManagerGetLatestInstanceIdForTableMessage ();

                string  getTableName                                            () const;
                UI32    getLatestInstanceId                                     () const;
                void    setLatestInstabceId                                     (const UI32 &latestInstanceId);

    // Noe the data members

    private :
        string m_tableName;
        UI32   m_latestInstanceId;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERGETLATESTINSTANCEIDFORTABLEMESSAGE_H
