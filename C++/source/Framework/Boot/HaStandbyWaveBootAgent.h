/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef STANDBYWAVEBOOTAGENT_H
#define STANDBYWAVEBOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"

namespace WaveNs
{

class HaStandbyWaveBootAgent : public WaveBootAgent
{
    private :
        virtual bool           isAPersistentBoot                            ();
        virtual bool           isToBeExcludedForEnableAndBoot               (const WaveServiceId& waveServiceId);
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInstall                    (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (const WaveServiceId &waveServiceId);
        virtual WaveBootReason getReason                                    () const;

    protected :
        ResourceId haInstallWaveServicesDuringPrePhaseStep       (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId haInstallWaveServicesStep                     (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId haBootWaveServicesDuringPrePhaseStep          (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId haBootLocalWaveServicesStep                   (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId haBootGlobalWaveServicesStep                  (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId haBootWaveServicesStep                        (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId resetLocationRole                              (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

    public :
                            HaStandbyWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~HaStandbyWaveBootAgent ();
        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);

    // now the data members

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // STANDBYWAVEBOOTAGENT_H
