/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERBASEDMESSAGINGBUS_H
#define WAVEBROKERBASEDMESSAGINGBUS_H

#include "Framework/Messaging/MessagingBus/WaveMessagingBus.h"

namespace WaveNs
{

class WaveBrokerBasedMessagingBus : public WaveMessagingBus
{
    private :
    protected :
    public :
                 WaveBrokerBasedMessagingBus (const string &name);
        virtual ~WaveBrokerBasedMessagingBus ();

    // Now the data types

    private :
    protected :
    public :
};

}

#endif // WAVEBROKERBASEDMESSAGINGBUS_H
