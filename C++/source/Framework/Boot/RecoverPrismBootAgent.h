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

        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedForEnableAndBoot               (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const WaveServiceId &prismServiceId);

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
