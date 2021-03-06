/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERINITIALIZEBEFOREBOOTCOMPLETEMESSAGE_H
#define PERSISTENCEOBJECTMANAGERINITIALIZEBEFOREBOOTCOMPLETEMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerInitializeBeforeBootCompleteMessage : public WaveMessage
{
    public:
                      PersistenceObjectManagerInitializeBeforeBootCompleteMessage ();
            virtual  ~PersistenceObjectManagerInitializeBeforeBootCompleteMessage ();

    protected:
    private:

    public:
    protected:
    private:
};

}

#endif //PERSISTENCEOBJECTMANAGERINITIALIZEBEFOREBOOTCOMPLETEMESSAGE_H
