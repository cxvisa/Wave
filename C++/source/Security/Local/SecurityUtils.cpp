/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                          *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/TraceUtils.h"
#include "Security/Local/SecurityLocalObjectManager.h"
#include "Security/Local/SecurityUtils.h"

#include <openssl/err.h>

namespace WaveNs
{

SSL_CTX *SecurityUtils::getPTlsSslContext ()
{
    return (SecurityLocalObjectManager::getPTlsSslContext ());
}

SSL_CTX *SecurityUtils::getPDtlsSslContext ()
{
    return (SecurityLocalObjectManager::getPDtlsSslContext ());
}

SSL_CTX *SecurityUtils::getPDtlsClientSslContext ()
{
    return (SecurityLocalObjectManager::getPDtlsClientSslContext ());
}

int sslErrorCallback (const char *pErrorString, size_t length, void *pUserData)
{
    WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "%s", pErrorString);

    return (0);
}

void SecurityUtils::traceSslErrors ()
{
    ERR_print_errors_cb (sslErrorCallback, NULL);
}

}
