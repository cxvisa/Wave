/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H
#define DATABASEOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include <string>

namespace WaveNs
{

class DatabaseObjectManagerExecuteTransactionMessage : public WaveMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                              DatabaseObjectManagerExecuteTransactionMessage (const string &sql);
                              DatabaseObjectManagerExecuteTransactionMessage ();
        virtual              ~DatabaseObjectManagerExecuteTransactionMessage ();

                const string &getSql                                         () const;
                      void    setSql                                         (const string &sql);
                      bool    getIsCommit                                    () const;
                      void    setIsCommit                                    (const bool &isCommit);
                      bool    getIsPrepare                                   () const;
                      void    setIsPrepare                                   (const bool &isPrepare);
    // Now the data members

    private :
        string m_sql;
        bool   m_isCommit;
        bool   m_isPrepare;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H
