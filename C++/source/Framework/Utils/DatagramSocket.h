/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATAGRAMSOCKET_H
#define DATAGRAMSOCKET_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class DatagramSocket
{
    private :
    protected :
    public :
         DatagramSocket ();
        virtual ~DatagramSocket ();

        bool isValid ();

        // Now the data members.

    private :
    protected :
        SI32 m_socket;

    public :
};

}

#endif // DATAGRAMSOCKET_H
