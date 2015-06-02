/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERDELAYEDTRANSACTIONMESSAGES_H
#define PERSISTENCEOBJECTMANAGERDELAYEDTRANSACTIONMESSAGES_H

#include "Framework/Messaging/Local/PrismMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerAddDelayedTransactionMessage : public PrismMessage
{
    private :
        void            setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceObjectManagerAddDelayedTransactionMessage    (const string &sql);
                        PersistenceObjectManagerAddDelayedTransactionMessage    ();
        virtual        ~PersistenceObjectManagerAddDelayedTransactionMessage    ();

                string  getSql                                                  () const;
                void    setSql                                                  (const string &sql);


    // Now the data members

    private :
                string  m_sql;

    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGERDELAYEDTRANSACTIONMESSAGES_H
