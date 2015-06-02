/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERUPDATEINSTANCEIDMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERUPDATEINSTANCEIDMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerUpdateInstanceIdMesssage : public PrismMessage
{
    public:
                      PersistenceLocalObjectManagerUpdateInstanceIdMesssage ();
            virtual  ~PersistenceLocalObjectManagerUpdateInstanceIdMesssage ();

    protected:
    private:

    public:
    protected:
    private:
};

}

#endif //PERSISTENCELOCALOBJECTMANAGERUPDATEINSTANCEIDMESSAGE_H
