/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERBACKUPMESSAGE_H
#define DATABASEOBJECTMANAGERBACKUPMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class DatabaseObjectManagerBackupMessage : public WaveMessage
{
    private :
    protected :
    public :
                        DatabaseObjectManagerBackupMessage (const string &backupFileName, const bool &pauseTheService = true);
        virtual        ~DatabaseObjectManagerBackupMessage ();

                string  getBackupFileName                  () const;
                void    setBackupFileName                  (const string &backupFileName);
                bool    getPauseTheService                 () const;
                void    setBackupAllSchema                 (const bool isNeeded);
                bool    getBackupAllSchema                 () const;
                bool    getDataOnlyBackup                  () const;
                void    setDataOnlyBackup                  (const bool dataOnlyBackup);

    // Noe the data members

    private :
        string m_backupFileName;
        bool   m_pauseTheService;
        bool   m_backupAllSchemas;
        bool   m_dataOnlyBackup;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERBACKUPMESSAGE_H
