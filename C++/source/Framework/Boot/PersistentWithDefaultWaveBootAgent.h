/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef PERSISTENTWITHDEFAULTWAVEBOOTAGENT_H
#define PERSISTENTWITHDEFAULTWAVEBOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"

namespace WaveNs
{

class PersistentWithDefaultWaveBootAgent : public WaveBootAgent
{
    private :
        virtual bool           isAPersistentBoot ();
        virtual WaveBootReason getReason         () const;

    protected :
    public :
                            PersistentWithDefaultWaveBootAgent                        (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~PersistentWithDefaultWaveBootAgent                        ();
        virtual ResourceId  execute                                                    (const WaveBootPhase &waveBootPhase);

                ResourceId  createFrameworkConfigurationFromPersistedConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
                ResourceId  connectToKnownLocationsStep                                (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PERSISTENTWITHDEFAULTWAVEBOOTAGENT_H
