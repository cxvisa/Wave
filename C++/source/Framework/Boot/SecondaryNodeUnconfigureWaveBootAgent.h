/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SECONDARYNODEUNCONFIGUREWAVEBOOTAGENT_H
#define SECONDARYNODEUNCONFIGUREWAVEBOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class SecondaryNodeUnconfigureWaveBootAgent : public WaveBootAgent
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
                                SecondaryNodeUnconfigureWaveBootAgent      (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual                ~SecondaryNodeUnconfigureWaveBootAgent      ();
        virtual ResourceId      execute                                     (const WaveBootPhase &waveBootPhase);

    //Now the data members

    private :
    protected :
    public :
};

}

#endif // SECONDARYNODEUNCONFIGUREWAVEBOOTAGENT_H
