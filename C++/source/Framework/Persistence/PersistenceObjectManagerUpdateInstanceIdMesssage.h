/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERUPDATEINSTANCEIDMESSAGE_H
#define PERSISTENCEOBJECTMANAGERUPDATEINSTANCEMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerUpdateInstanceIdMesssage : public WaveMessage
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
