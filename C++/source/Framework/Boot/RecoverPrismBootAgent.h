/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef RECOVERWAVEBOOTAGENT_H
#define RECOVERWAVEBOOTAGENT_H

#include "Framework/Boot/FirstTimeWaveBootAgent.h"
#include "Framework/Database/DatabaseObjectManagerShutdownMessage.h"

namespace WaveNs
{

class RecoverWaveBootAgent : public FirstTimeWaveBootAgent
{
    private :

        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedForEnableAndBoot               (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const WaveServiceId &waveServiceId);

    protected :
    public :
                 RecoverWaveBootAgent   (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual ~RecoverWaveBootAgent   ();

        virtual ResourceId  execute                              (const WaveBootPhase &waveBootPhase);
                ResourceId  shutdownDatabaseStep                 (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
                ResourceId  updateFrameworkConfigurationToDefaultStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

    // Now the data members

    private :
                            WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // RECOVERWAVEBOOTAGENT_H
