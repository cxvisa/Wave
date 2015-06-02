/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef STANDBYPRISMBOOTAGENT_H
#define STANDBYPRISMBOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"

namespace WaveNs
{

class HaStandbyPrismBootAgent : public PrismBootAgent
{
    private :
        virtual bool           isAPersistentBoot                            ();
        virtual bool           isToBeExcludedForEnableAndBoot               (const PrismServiceId& prismServiceId);
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const PrismServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInstall                    (const PrismServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const PrismServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const PrismServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (const PrismServiceId &prismServiceId);
        virtual WaveBootReason getReason                                    () const;

    protected :
        ResourceId haInstallPrismServicesDuringPrePhaseStep       (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId haInstallPrismServicesStep                     (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId haBootPrismServicesDuringPrePhaseStep          (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId haBootLocalPrismServicesStep                   (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId haBootGlobalPrismServicesStep                  (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId haBootPrismServicesStep                        (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId resetLocationRole                              (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

    public :
                            HaStandbyPrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~HaStandbyPrismBootAgent ();
        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);

    // now the data members

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // STANDBYPRISMBOOTAGENT_H
