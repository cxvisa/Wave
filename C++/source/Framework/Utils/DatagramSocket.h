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


        // Now the data members.

    private :
    protected :
        SI32  m_socket;

        SSL  *m_pSsl;

    public :
};

}

#endif // DATAGRAMSOCKET_H
