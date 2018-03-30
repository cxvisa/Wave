/**************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLIENTDATAGRAMSOCKET_H
#define CLIENTDATAGRAMSOCKET_H

#include "Framework/Utils/DatagramSocket.h"

namespace WaveNs
{

class ClientDatagramSocket : public DatagramSocket
{
    private :
    protected :
    public :
                       ClientDatagramSocket (const string &ipAddress, const SI32 &port);
        virtual       ~ClientDatagramSocket ();

        virtual void   enableSecurity       ();

        virtual bool   connect              (const UI32 &milliSecondsToWaitFor = 1000);

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // CLIENTDATAGRAMSOCKET_H
