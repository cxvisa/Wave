/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERENABLETRANSACTIONMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERENABLETRANSACTIONMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerEnableTransactionMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerEnableTransactionMessage ();
        virtual        ~PersistenceLocalObjectManagerEnableTransactionMessage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGERENABLETRANSACTIONMESSAGE_H
