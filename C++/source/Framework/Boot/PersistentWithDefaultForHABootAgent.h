/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef PERSISTENTWITHDEFAULTFORHABOOTAGENT_H
#define PERSISTENTWITHDEFAULTFORHABOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"

namespace WaveNs
{

class PersistentWithDefaultForHABootAgent : public PrismBootAgent
{
    private :
        virtual bool           isAPersistentBoot ();
        virtual WaveBootReason getReason         () const;

    protected :
    public :
                            PersistentWithDefaultForHABootAgent                        (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~PersistentWithDefaultForHABootAgent                        ();
        virtual ResourceId  execute                                                    (const WaveBootPhase &waveBootPhase);

                ResourceId  createFrameworkConfigurationFromPersistedConfigurationStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId  connectToKnownLocationsStep                                (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        virtual bool        isToBeExcludedFromInstallDuringPrePhase                    (const WaveServiceId &prismServiceId);
        virtual bool        isToBeExcludedFromInstall                                  (const WaveServiceId &prismServiceId);
        virtual bool        isToBeExcludedFromInitializeDuringPrePhase                 (const WaveServiceId &prismServiceId);
        virtual bool        isToBeExcludedFromInitializePhase                          (const WaveServiceId &prismServiceId);
        virtual bool        isToBeExcludedForEnableAndBoot                             (const WaveServiceId& prismServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PERSISTENTWITHDEFAULTFORHABOOTAGENT_H
