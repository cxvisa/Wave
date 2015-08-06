/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERRESTOREMESSAGE_H
#define DATABASEOBJECTMANAGERRESTOREMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class DatabaseObjectManagerRestoreMessage : public WaveMessage
{
    private :
    protected :
    public :
                        DatabaseObjectManagerRestoreMessage (const string &fileToRestoreFrom);
        virtual        ~DatabaseObjectManagerRestoreMessage ();

                string  getFileToRestoreFrom                () const;
                bool    getRestoreSchema                    () const;
                void    setRestoreSchema                    (const bool isRestoreNeeded);
                bool    getDataOnlyRestore                  () const;
                void    setDataOnlyRestore                  (const bool dataOnlyRestore);
                bool    getSaveConfiguration                () const;
                void    setSaveConfiguration                (const bool saveConfiguration);

    // Now the data members

    private :
        string m_fileToRestoreFrom;
        bool   m_restoreSchema;
        bool   m_dataOnlyRestore;
        bool   m_saveConfiguration;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERRESTOREMESSAGE_H
