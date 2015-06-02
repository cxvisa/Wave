/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FIRSTTIMEPRISMBOOTAGENT_H
#define FIRSTTIMEPRISMBOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"

namespace WaveNs
{

class FirstTimePrismBootAgent : public PrismBootAgent
{
    private :
        virtual WaveBootReason getReason () const;

    protected :
    public :
                 FirstTimePrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual ~FirstTimePrismBootAgent ();
        virtual  ResourceId  execute      (const WaveBootPhase &waveBootPhase);

    // Now the data members

    private :
    protected :
                 ResourceId savePrismConfigurationStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
    public :
};

}

#endif // FIRSTTIMEPRISMBOOTAGENT_H
