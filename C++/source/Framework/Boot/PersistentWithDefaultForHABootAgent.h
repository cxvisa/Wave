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
        virtual bool        isToBeExcludedFromInstallDuringPrePhase                    (const PrismServiceId &prismServiceId);
        virtual bool        isToBeExcludedFromInstall                                  (const PrismServiceId &prismServiceId);
        virtual bool        isToBeExcludedFromInitializeDuringPrePhase                 (const PrismServiceId &prismServiceId);
        virtual bool        isToBeExcludedFromInitializePhase                          (const PrismServiceId &prismServiceId);
        virtual bool        isToBeExcludedForEnableAndBoot                             (const PrismServiceId& prismServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PERSISTENTWITHDEFAULTFORHABOOTAGENT_H
