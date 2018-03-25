/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                          *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Security/Local/SecurityUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Security/Local/SecurityLocalObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

SecurityLocalObjectManager::SecurityLocalObjectManager ()
        : WaveLocalObjectManager (getServiceName ()),
          m_pTlsSslContext       (NULL),
          m_pDtlsSslContext      (NULL)
{
}

SecurityLocalObjectManager::~SecurityLocalObjectManager ()
{
}

string SecurityLocalObjectManager::getServiceName ()
{
    return ("Security Local");
}

SecurityLocalObjectManager *SecurityLocalObjectManager::getInstance ()
{
    static SecurityLocalObjectManager *pSecurityLocalObjectManager = NULL;

    if (NULL == pSecurityLocalObjectManager)
    {
        pSecurityLocalObjectManager = new SecurityLocalObjectManager ();
    }

    WaveNs::waveAssert (NULL != pSecurityLocalObjectManager, __FILE__, __LINE__);

    return (pSecurityLocalObjectManager);
}

void SecurityLocalObjectManager::initialize (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&SecurityLocalObjectManager::initializeSslLibraryStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SecurityLocalObjectManager::initializeServerContextStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SecurityLocalObjectManager::initializeLoadCertificatesForTlsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SecurityLocalObjectManager::initializeLoadCertificatesForDtlsStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SecurityLocalObjectManager::initializeSetPeerValidationStep),

        reinterpret_cast<WaveLinearSequencerStep> (&SecurityLocalObjectManager::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SecurityLocalObjectManager::waveLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pWaveAsynchronousContextForBootPhases, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void SecurityLocalObjectManager::initializeSslLibraryStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SecurityLocalObjectManager::initializeSslLibraryStep : Entering ...");

    SSL_library_init           ();

    OpenSSL_add_all_algorithms ();
    SSL_load_error_strings     ();

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void SecurityLocalObjectManager::initializeServerContextStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SecurityLocalObjectManager::initializeServerContextStep : Entering ...");

    const SSL_METHOD *pTlsSslMethod = TLS_server_method ();

    SSL_CTX *pTlsSslContext = SSL_CTX_new (pTlsSslMethod);

    if (NULL == pTlsSslContext)
    {
        SecurityUtils::traceSslErrors ();
        waveAssert (false, __FILE__, __LINE__);
    }

    m_pTlsSslContext = pTlsSslContext;

    const SSL_METHOD *pDtlsSslMethod = DTLS_server_method ();

    SSL_CTX *pDtlsSslContext = SSL_CTX_new (pDtlsSslMethod);

    if (NULL == pDtlsSslContext)
    {
        SecurityUtils::traceSslErrors ();
        waveAssert (false, __FILE__, __LINE__);
    }

    m_pDtlsSslContext = pDtlsSslContext;

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void SecurityLocalObjectManager::initializeLoadCertificatesForTlsStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SecurityLocalObjectManager::initializeLoadCertificatesForTlsStep : Entering ...");

    if (0 >= (SSL_CTX_use_certificate_file (m_pTlsSslContext, "pki/public-private.pem", SSL_FILETYPE_PEM)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (0 >= (SSL_CTX_use_PrivateKey_file (m_pTlsSslContext, "pki/public-private.pem", SSL_FILETYPE_PEM)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (false == (SSL_CTX_check_private_key (m_pTlsSslContext)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (false == (SSL_CTX_load_verify_locations (m_pTlsSslContext, "pki/cacert.pem", NULL)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

void SecurityLocalObjectManager::initializeLoadCertificatesForDtlsStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SecurityLocalObjectManager::initializeLoadCertificatesForDtlsStep : Entering ...");

    if (0 >= (SSL_CTX_use_certificate_file (m_pDtlsSslContext, "pki/public-private.pem", SSL_FILETYPE_PEM)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (0 >= (SSL_CTX_use_PrivateKey_file (m_pDtlsSslContext, "pki/public-private.pem", SSL_FILETYPE_PEM)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (false == (SSL_CTX_check_private_key (m_pDtlsSslContext)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    if (false == (SSL_CTX_load_verify_locations (m_pDtlsSslContext, "pki/cacert.pem", NULL)))
    {
        SecurityUtils::traceSslErrors ();
        pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_ERROR);
        return;
    }

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}
int sslVerifyCallback (int preVerifyOk, X509_STORE_CTX *pX509Context)
{
    if (0 == preVerifyOk)
    {
        WaveNs::trace (TRACE_LEVEL_ERROR, "Certificate Verification Failed :");

        char buffer[256];

        X509 *pCertificate = X509_STORE_CTX_get_current_cert (pX509Context);

        X509_NAME_oneline (X509_get_subject_name (pCertificate), buffer, 256);

        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "    Subject Name: %s", buffer);

        X509_NAME_oneline (X509_get_issuer_name (pCertificate), buffer, 256);

        WaveNs::tracePrintf (TRACE_LEVEL_ERROR, true, false, "    Issuer  Name: %s", buffer);
    }
    else
    {
        WaveNs::trace (TRACE_LEVEL_SUCCESS, "Certificate Verification Succeeded :");

        char buffer[256];

        X509 *pCertificate = X509_STORE_CTX_get_current_cert (pX509Context);

        X509_NAME_oneline (X509_get_subject_name (pCertificate), buffer, 256);

        WaveNs::tracePrintf (TRACE_LEVEL_SUCCESS, true, false, "    Subject Name: %s", buffer);

        X509_NAME_oneline (X509_get_issuer_name (pCertificate), buffer, 256);

        WaveNs::tracePrintf (TRACE_LEVEL_SUCCESS, true, false, "    Issuer  Name: %s", buffer);
    }

    return (preVerifyOk);
}

void SecurityLocalObjectManager::initializeSetPeerValidationStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SecurityLocalObjectManager::initializeSetPeerValidationStep : Entering ...");

    SSL_CTX_set_verify (m_pTlsSslContext,  SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, sslVerifyCallback);
    SSL_CTX_set_verify (m_pDtlsSslContext, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, sslVerifyCallback);

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

SSL_CTX *SecurityLocalObjectManager::getPTlsSslContext ()
{
    return ((getInstance ())->m_pTlsSslContext);
}

SSL_CTX *SecurityLocalObjectManager::getPDtlsSslContext ()
{
    return ((getInstance ())->m_pDtlsSslContext);
}

}

