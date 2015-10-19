/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMINITIALIZEWORKERSTARTPRISMSERVICESCONTEXT_H
#define PRISMINITIALIZEWORKERSTARTPRISMSERVICESCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Framework/Core/WaveFrameworkObjectManagerInitializeWorker.h"

namespace WaveNs
{

class PrismBootAgent;

class WaveFrameworkInitializeWorkerStartServicesContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                        WaveFrameworkInitializeWorkerStartServicesContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                       ~WaveFrameworkInitializeWorkerStartServicesContext ();
        void            setPrismBootMode                                   (PrismBootMode prismBootMode);
        PrismBootMode   getPrismBootMode                                   () const;
        void            setWaveBootPhase                                   (const WaveBootPhase &waveBootPhase);
        WaveBootPhase   getWaveBootPhase                                   () const;
        void            setPPrismBootAgent                                 (PrismBootAgent *pPrismBootAgent);
        PrismBootAgent *getPPrismBootAgent                                 ();
        bool            isSchemaChangedOnFwdl                              () const;
        void            setSchemaChangedOnFwdl                             (bool hasChanged);
        bool            getIsSchemaUpgradedSuccessfully                    () const;
        void            setIsSchemaUpgradedSuccessfully                    (const bool &isSchemaUpgradedSuccessfully);

    // Now the data members

    private :
        PrismBootMode   m_prismBootMode;
        WaveBootPhase   m_waveBootPhase;
        PrismBootAgent *m_pPrismBootAgent;
        bool            m_isSchemaChangedOnFwdl;
        bool            m_isSchemaUpgradedSuccessfully;

    protected :
    public :
};

}

#endif // PRISMINITIALIZEWORKERSTARTPRISMSERVICESCONTEXT_H
