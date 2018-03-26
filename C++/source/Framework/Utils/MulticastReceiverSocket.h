/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MULTICASTRECEIVERSOCKET_H
#define MULTICASTRECEIVERSOCKET_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/MulticastSocket.h"

namespace WaveNs
{

class MulticastReceiverSocket : public MulticastSocket
{
    private :
    protected :
    public :
              MulticastReceiverSocket (const string &groupIpAddress, const SI32 &port);
             ~MulticastReceiverSocket ();

        bool  addGroupMembership      (const string &groupIpAddress);

        // Now the data members.

    private :
    protected :
    public :
};

}

#endif // MULTICASTRECEIVERSOCKET_H
