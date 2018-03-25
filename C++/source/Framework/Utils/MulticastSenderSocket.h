/**************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MULTICASTSENDERSOCKET_H
#define MULTICASTSENDERSOCKET_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/MulticastSocket.h"

namespace WaveNs
{

class MulticastSenderSocket : public MulticastSocket
{
    private :
    protected :
    public :
         MulticastSenderSocket (const string &groupIpAddress, const SI32 &port);
        virtual ~MulticastSenderSocket ();

        virtual bool send (const string &data);

        // Now the data members.

    private :
        sockaddr_in m_groupSocketAddress;

    protected :
    public :
};

}

#endif // MULTICASTSENDERSOCKET_H
