/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERGETDBACCESSDETAILSMESSAGE_H
#define DATABASEOBJECTMANAGERGETDBACCESSDETAILSMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class DatabaseObjectManagerGetDbAccessDetailsMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        DatabaseObjectManagerGetDbAccessDetailsMessage ();
        virtual        ~DatabaseObjectManagerGetDbAccessDetailsMessage ();

                string  getDatabaseName                                () const;
                void    setDatabaseName                                (const string &databaseName);

                UI32    getPort                                        () const;
                void    setPort                                        (const UI32 &port);

    // Now the Data Members

    private :
        string m_databaseName;
        UI32   m_port;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERGETDBACCESSDETAILSMESSAGE_H
