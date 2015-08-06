/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerExecuteTransactionMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                              PersistenceLocalObjectManagerExecuteTransactionMessage (const string &sql, const UI32 &transactionId);
                              PersistenceLocalObjectManagerExecuteTransactionMessage ();
        virtual              ~PersistenceLocalObjectManagerExecuteTransactionMessage ();

                const string &getSql                                                 () const;
                      void    setSql                                                 (const string &sql);
                      bool    getIsCommit                                            () const;
                      void    setIsCommit                                            (const bool &isCommit);
                      bool    getIsRollback                                          () const;
                      void    setIsRollback                                          (const bool &isRollback);
                      bool    getIsPrepare                                           () const;
                      void    setIsPrepare                                           (const bool &isPrepare);
                      UI32    getTransactionId                                       () const;
                      void    setTransactionId                                       (const UI32 &transactionId);
                      bool    getIsConfigurationChange                               () const;
                      void    setIsConfigurationChange                               (const bool &isConfigurationChange);
                      bool    getIsConfigurationTimeChange                           () const;
                      void    setIsConfigurationTimeChange                           (const bool &isConfigurationTimeChange);

                      void    setAnyConfigurationChangeTrackingNumber                (const UI64 &trackingNumber);
                      UI64    getAnyConfigurationChangeTrackingNumber                () const;

    // Now the data members

    private :
        string m_sql;
        bool   m_isCommit;
        bool   m_isRollback;
        UI32   m_transactionId;
        bool   m_isPrepare;
        bool   m_isConfigurationChange;
        bool   m_isConfigurationTimeChange;
        UI64   m_anyConfigurationChangeTrackingNumber;

    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H
