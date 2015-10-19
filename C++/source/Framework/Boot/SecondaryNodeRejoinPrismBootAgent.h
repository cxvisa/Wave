/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                    *
 ***************************************************************************/

#ifndef SECONDARYNODEREJOINWAVEBOOTAGENT_H
#define SECONDARYNODEREJOINWAVEBOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"

namespace WaveNs
{
///Class:
///SecondaryNodeRejoinWaveBootAgent
/// 
///Description:
/// This Class serves as the boot agent for rebooting of services
/// during processing of phase1 and phase2 rejoin messages on the 
/// secondary.

class SecondaryNodeRejoinWaveBootAgent : public WaveBootAgent
{
    private :
	//Rejoin Boot is always persistent
        virtual bool           isAPersistentBoot                       ();
	//QUESTION: SAGAR
        virtual bool           isToBeExcludedForEnableAndBoot          (const WaveServiceId& waveServiceId);

        virtual bool           willBeAPrimaryLocation                  ();

        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (WaveServiceId waveServiceId);
	//Reason for boot
        virtual WaveBootReason getReason                               () const;

    protected :
    public :
                            SecondaryNodeRejoinWaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~SecondaryNodeRejoinWaveBootAgent ();

	//This method implements the pre and the post boot phase
	//It calls the steps alreday implemented in the base class
        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // SECONDARYNODEREJOINWAVEBOOTAGENT_H
