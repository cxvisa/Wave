/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATAGRAMSOCKET_H
#define DATAGRAMSOCKET_H

#include "Framework/Types/Types.h"

#include <openssl/ssl.h>

namespace WaveNs
{

class FixedSizeBuffer;

class DatagramSocket
{
    private :
    protected :
    public :
                      DatagramSocket     ();
        virtual      ~DatagramSocket     ();

                bool   isValid           ();

                void   enableSecurity    ();
                void   disableSecurity   ();
                bool   isSecurityEnabled ();
                SSL   *getPSsl           ();

                bool   accept            ();

        virtual bool   send              (sockaddr *pSockAddr, const string &data);

        virtual bool   receive           (string &dataString, string &fromIpAddress, SI32 &fromPort);
        virtual SI32   receive           (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort);
        virtual SI32   receive           (FixedSizeBuffer * const pFixedSizeBuffer, string &fromIpAddress, SI32 &fromPort);
        virtual SI32   receiveAll        (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort);

        // Now the data members.

    private :
    protected :
        static const UI32 s_maximumDataLengthToReceive = 4 * 1024; // 4 KB - We will read 4 KB at a time - but there is no limit on the message size that can be sent across.

        SI32         m_socket;

        sockaddr_in  m_fromSocketAddres;
        socklen_t    m_fromSocketLength;

        SSL         *m_pSsl;

    public :
};

}

#endif // DATAGRAMSOCKET_H
