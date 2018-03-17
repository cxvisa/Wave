/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                          *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SECURITYUTILS_H
#define SECURITYUTILS_H

#include <openssl/ossl_typ.h>

namespace WaveNs
{

class SecurityUtils
{
    private :
    protected :
    public :
        static SSL_CTX *getPSslContext ();
        static void     traceSslErrors ();

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // SECURITYUTILS_H
