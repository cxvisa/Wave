/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FIRSTTIMEWAVEBOOTAGENT_H
#define FIRSTTIMEWAVEBOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"

namespace WaveNs
{

class FirstTimeWaveBootAgent : public WaveBootAgent
{
    private :
        virtual WaveBootReason getReason () const;

    protected :
    public :
                 FirstTimeWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual ~FirstTimeWaveBootAgent ();
        virtual  ResourceId  execute      (const WaveBootPhase &waveBootPhase);

    // Now the data members

    private :
    protected :
                 ResourceId saveWaveConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
    public :
};

}

#endif // FIRSTTIMEWAVEBOOTAGENT_H
