/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                          *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Security/Local/SecurityLocalObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

SecurityLocalObjectManager::SecurityLocalObjectManager ()
        : WaveLocalObjectManager (getServiceName ()),
          m_pSslContext          (NULL)
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
}

void SecurityLocalObjectManager::initializeServerContextStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SecurityLocalObjectManager::initializeServerContextStep : Entering ...");

    const SSL_METHOD *pSslMethod = TLS_server_method ();

    SSL_CTX *pSslContext = SSL_CTX_new (pSslMethod);

    if (NULL == pSslContext)
    {
        ERR_print_errors_fp (stderr);
        waveAssert (false, __FILE__, __LINE__);
    }

    m_pSslContext = pSslContext;

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}

