/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef PERSISTENTWITHDEFAULTFORHABOOTAGENT_H
#define PERSISTENTWITHDEFAULTFORHABOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"

namespace WaveNs
{

class PersistentWithDefaultForHABootAgent : public WaveBootAgent
{
    private :
        virtual bool           isAPersistentBoot ();
        virtual WaveBootReason getReason         () const;

    protected :
    public :
                            PersistentWithDefaultForHABootAgent                        (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~PersistentWithDefaultForHABootAgent                        ();
        virtual ResourceId  execute                                                    (const WaveBootPhase &waveBootPhase);

                ResourceId  createFrameworkConfigurationFromPersistedConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
                ResourceId  connectToKnownLocationsStep                                (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        virtual bool        isToBeExcludedFromInstallDuringPrePhase                    (const WaveServiceId &waveServiceId);
        virtual bool        isToBeExcludedFromInstall                                  (const WaveServiceId &waveServiceId);
        virtual bool        isToBeExcludedFromInitializeDuringPrePhase                 (const WaveServiceId &waveServiceId);
        virtual bool        isToBeExcludedFromInitializePhase                          (const WaveServiceId &waveServiceId);
        virtual bool        isToBeExcludedForEnableAndBoot                             (const WaveServiceId& waveServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PERSISTENTWITHDEFAULTFORHABOOTAGENT_H
