/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                          *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SECURITYLOCALOBJECTMANAGER_H
#define SECURITYLOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;
class WaveLinearSequencerContext;

class SecurityLocalObjectManager : public WaveLocalObjectManager
{
    private:
             SecurityLocalObjectManager            ();

        void initialize                            (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        void initializeSslLibraryStep              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void initializeServerContextStep           (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void initializeLoadCertificatesForTlsStep  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void initializeLoadCertificatesForDtlsStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void initializeSetPeerValidationStep       (WaveLinearSequencerContext *pWaveLinearSequencerContext);

    protected:
    public:
        virtual ~SecurityLocalObjectManager ();

        static string                      getServiceName ();
        static SecurityLocalObjectManager *getInstance    ();

        static SSL_CTX                    *getPTlsSslContext  ();
        static SSL_CTX                    *getPDtlsSslContext ();

        // Now the data members

    private:
        SSL_CTX *m_pTlsSslContext;
        SSL_CTX *m_pDtlsSslContext;

    protected:
    public:
};

}

#endif // SECURITYLOCALOBJECTMANAGER_H
