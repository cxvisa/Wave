/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                    *
 ***************************************************************************/

#ifndef SECONDARYNODEREJOINPRISMBOOTAGENT_H
#define SECONDARYNODEREJOINPRISMBOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"

namespace WaveNs
{
///Class:
///SecondaryNodeRejoinPrismBootAgent
/// 
///Description:
/// This Class serves as the boot agent for rebooting of services
/// during processing of phase1 and phase2 rejoin messages on the 
/// secondary.

class SecondaryNodeRejoinPrismBootAgent : public PrismBootAgent
{
    private :
	//Rejoin Boot is always persistent
        virtual bool           isAPersistentBoot                       ();
	//QUESTION: SAGAR
        virtual bool           isToBeExcludedForEnableAndBoot          (const WaveServiceId& prismServiceId);

        virtual bool           willBeAPrimaryLocation                  ();

        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (WaveServiceId prismServiceId);
	//Reason for boot
        virtual WaveBootReason getReason                               () const;

    protected :
    public :
                            SecondaryNodeRejoinPrismBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~SecondaryNodeRejoinPrismBootAgent ();

	//This method implements the pre and the post boot phase
	//It calls the steps alreday implemented in the base class
        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // SECONDARYNODEREJOINPRISMBOOTAGENT_H
