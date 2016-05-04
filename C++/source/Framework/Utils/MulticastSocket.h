/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MULTICASTSOCKET_H
#define MULTICASTSOCKET_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/DatagramSocket.h"

namespace WaveNs
{

class MulticastSocket : public DatagramSocket
{
    private :
    protected :
    public :
         MulticastSocket ();
        virtual ~MulticastSocket ();

        bool setMulticastLoopback   ();
        bool clearMulticastLoopback ();

        virtual bool send (sockaddr *pSockAddr, const string &data);

        // Now the data members.

    private :
        in_addr m_localInterface;

    protected :
    public :
};

}

#endif // MULTICASTSOCKET_H
