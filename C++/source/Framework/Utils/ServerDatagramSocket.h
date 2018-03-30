/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SERVERDATAGRAMSOCKET_H
#define SERVERDATAGRAMSOCKET_H

#include "Framework/Utils/DatagramSocket.h"

namespace WaveNs
{

class ServerDatagramSocket : public DatagramSocket
{
    private :
    protected :
    public :
                 ServerDatagramSocket ();
                 ServerDatagramSocket (const SI32 &port);
        virtual ~ServerDatagramSocket ();

        // Now the data members

    private :

    protected :
    public :
};

}

#endif // SERVERDATAGRAMSOCKET_H
