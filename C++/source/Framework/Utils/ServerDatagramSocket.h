/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/DatagramSocket.h"

namespace WaveNs
{

class ServerDatagramSocket : public DatagramSocket
{
    private :
    protected :
    public :
                      ServerDatagramSocket (const SI32 &port);
        virtual      ~ServerDatagramSocket ();

                bool  accept               ();

        // Now the data members

    private :

    protected :
    public :
};

}
