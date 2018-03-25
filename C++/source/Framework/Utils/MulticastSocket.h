/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
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
                      MulticastSocket        ();
        virtual      ~MulticastSocket        ();

                bool  setMulticastLoopback   ();
                bool  clearMulticastLoopback ();

        // Now the data members.

    private :
        in_addr m_localInterface;

    protected :
    public :
};

}

#endif // MULTICASTSOCKET_H
