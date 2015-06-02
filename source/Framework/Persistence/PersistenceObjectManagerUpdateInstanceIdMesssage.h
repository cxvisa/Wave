/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERUPDATEINSTANCEIDMESSAGE_H
#define PERSISTENCEOBJECTMANAGERUPDATEINSTANCEMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerUpdateInstanceIdMesssage : public PrismMessage
{
    public:
                      PersistenceObjectManagerUpdateInstanceIdMesssage ();
            virtual  ~PersistenceObjectManagerUpdateInstanceIdMesssage ();

    protected:
    private:

    public:
    protected:
    private:
};

}

#endif //PERSISTENCEOBJECTMANAGERUPDATEINSTANCEMESSAGE_H
