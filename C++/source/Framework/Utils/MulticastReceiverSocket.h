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

class FixedSizeBuffer;

class MulticastReceiverSocket : public MulticastSocket
{
    private :
    protected :
    public :
              MulticastReceiverSocket (const string &groupIpAddress, const SI32 &port);
             ~MulticastReceiverSocket ();

        bool  addGroupMembership      (const string &groupIpAddress);

        bool   receive                (string &dataString, string &fromIpAddress, SI32 &fromPort);
        SI32   receive                (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort);
        SI32   receive                (FixedSizeBuffer * const pFixedSizeBuffer, string &fromIpAddress, SI32 &fromPort);
        SI32   receiveAll             (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort);

        // Now the data members.

    private :
        static const UI32        s_maximumDataLengthToReceive = 4 * 1024; // 4 KB - We will read 4 KB at a time - but there is no limit on the message size that can be sent across.

                     sockaddr_in m_fromSocketAddres;
                     socklen_t   m_fromSocketLength;

    protected :
    public :
};

}

#endif // MULTICASTRECEIVERSOCKET_H
