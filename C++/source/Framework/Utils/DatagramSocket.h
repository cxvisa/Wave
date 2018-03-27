/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
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

        virtual void   enableSecurity    ();
                void   disableSecurity   ();
                bool   isSecurityEnabled ();
                SSL   *getPSsl           ();

                bool   accept            ();
                bool   connect           ();

                bool   getIsAccepted     () const;
                void   setIsAccepted     (const bool &isAccepted);

                bool   getIsConnected    () const;
                void   setIsConnected    (const bool &isConnected);

        virtual bool   send              (sockaddr *pSockAddr, const string &data);

        virtual bool   receive           (string &dataString, string &fromIpAddress, SI32 &fromPort);
        virtual SI32   receive           (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort);
        virtual SI32   receive           (FixedSizeBuffer * const pFixedSizeBuffer, string &fromIpAddress, SI32 &fromPort);
        virtual SI32   receiveAll        (UI8 *pBuffer, const UI32 maximumBufferLength, string &fromIpAddress, SI32 &fromPort);

        virtual SI32   receive           (UI8 *pBuffer, const UI32 maximumBufferLength);
        virtual bool   receive           (string &dataString);

        virtual SI32   send              (UI8 *pBuffer, const UI32 maximumBufferLength);
        virtual bool   send              (const string &dataString);

        // Now the data members.

    private :
    protected :
        static const UI32 s_maximumDataLengthToReceive = 4 * 1024; // 4 KB - We will read 4 KB at a time - but there is no limit on the message size that can be sent across.

        SI32         m_socket;

        sockaddr_in  m_fromSocketAddres;
        socklen_t    m_fromSocketLength;

        SSL         *m_pSsl;

        bool         m_isAccepted;
        bool         m_isConnected;

    public :
};

}

#endif // DATAGRAMSOCKET_H
