/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SECONDARYNODEUNCONFIGUREPRISMBOOTAGENT_H
#define SECONDARYNODEUNCONFIGUREPRISMBOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class SecondaryNodeUnconfigurePrismBootAgent : public PrismBootAgent
{
    private :
        virtual bool            isAPersistentBoot                           ();
        virtual bool            isToBeExcludedForEnableAndBoot              (const WaveServiceId &waveServiceId);
        virtual bool            isToBeExcludedFromInitializeDuringPrePhase  (const WaveServiceId &waveServiceId);
        virtual bool            isToBeExcludedFromInitializePhase           (const WaveServiceId &waveServiceId);
        virtual bool            willBeAPrimaryLocation                      ();
        virtual WaveBootReason  getReason                                   () const;

    protected :
    public :
                                SecondaryNodeUnconfigurePrismBootAgent      (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual                ~SecondaryNodeUnconfigurePrismBootAgent      ();
        virtual ResourceId      execute                                     (const WaveBootPhase &waveBootPhase);

    //Now the data members

    private :
    protected :
    public :
};

}

#endif // SECONDARYNODEUNCONFIGUREPRISMBOOTAGENT_H
