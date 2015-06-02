/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERSHUTDOWNMESSAGE_H
#define DATABASEOBJECTMANAGERSHUTDOWNMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class DatabaseObjectManagerShutdownMessage : public ManagementInterfaceMessage
{
    private :
    protected :
    public :
                            DatabaseObjectManagerShutdownMessage    ();
                            DatabaseObjectManagerShutdownMessage    (const string &databaseDirectory);
                            DatabaseObjectManagerShutdownMessage    (const bool &isShutdownOnReboot);
        virtual            ~DatabaseObjectManagerShutdownMessage    ();
        virtual  void       setupAttributesForSerialization         ();

        void                setDatabaseDirectory                    (const string &databaseDirectory);
        string              getDatabaseDirectory                    () const;

        void                setIsShutdownOnReboot                   (const bool &isShutdownOnReboot);
        bool                getIsShutdownOnReboot                   () const;
    // Now the data members

    private :
        string                      m_databaseDirectory;
        bool                        m_isShutdownOnReboot;
    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGEREMPTYMESSAGE_H
