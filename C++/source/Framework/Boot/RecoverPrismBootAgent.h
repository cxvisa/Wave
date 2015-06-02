/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef RECOVERPRISMBOOTAGENT_H
#define RECOVERPRISMBOOTAGENT_H

#include "Framework/Boot/FirstTimePrismBootAgent.h"
#include "Framework/Database/DatabaseObjectManagerShutdownMessage.h"

namespace WaveNs
{

class RecoverPrismBootAgent : public FirstTimePrismBootAgent
{
    private :

        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const PrismServiceId &prismServiceId);
        virtual bool           isToBeExcludedForEnableAndBoot               (const PrismServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const PrismServiceId &prismServiceId);

    protected :
    public :
                 RecoverPrismBootAgent   (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual ~RecoverPrismBootAgent   ();

        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);
                ResourceId  shutdownDatabaseStep                 (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId  updateFrameworkConfigurationToDefaultStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

    // Now the data members

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // RECOVERPRISMBOOTAGENT_H
