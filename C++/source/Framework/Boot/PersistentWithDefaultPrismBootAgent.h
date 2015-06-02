/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef PERSISTENTWITHDEFAULTPRISMBOOTAGENT_H
#define PERSISTENTWITHDEFAULTPRISMBOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"

namespace WaveNs
{

class PersistentWithDefaultPrismBootAgent : public PrismBootAgent
{
    private :
        virtual bool           isAPersistentBoot ();
        virtual WaveBootReason getReason         () const;

    protected :
    public :
                            PersistentWithDefaultPrismBootAgent                        (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~PersistentWithDefaultPrismBootAgent                        ();
        virtual ResourceId  execute                                                    (const WaveBootPhase &waveBootPhase);

                ResourceId  createFrameworkConfigurationFromPersistedConfigurationStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId  connectToKnownLocationsStep                                (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PERSISTENTWITHDEFAULTPRISMBOOTAGENT_H
