/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PERSISTENTWAVEBOOTAGENT_H
#define PERSISTENTWAVEBOOTAGENT_H

#include "Framework/Boot/WaveBootAgent.h"

namespace WaveNs
{

class PersistentWaveBootAgent : public WaveBootAgent
{
    private :
        virtual bool           isAPersistentBoot                                          ();
        virtual WaveBootReason getReason                                                  () const;
        virtual bool           getRollBackFlag                                            () const;

                void           cleanPreparedTransactions                                  ();
                void           emptyDatabaseToRollBack                                    ();
                void           reloadPreviousDataBase                                     ();
//                void           rollbackCfgFile                                            ();

        virtual bool           isToBeExcludedForEnableAndBoot                             (const WaveServiceId& waveServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase                 (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInitializePhase                          (const WaveServiceId &waveServiceId);

    protected :
    public :
                            PersistentWaveBootAgent                                   (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~PersistentWaveBootAgent                                   ();
        virtual ResourceId  execute                                                    (const WaveBootPhase &waveBootPhase);

                ResourceId  createFrameworkConfigurationFromPersistedConfigurationStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
                ResourceId  connectToKnownLocationsStep                                (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
                ResourceId  rollBackDataBase                                           (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
                ResourceId  resetLocationRole                                          (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
                ResourceId  disconnectFromAllConnectedLocations                        (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

    // Now the data members

    private :
                bool          m_isRollBackDataBaseValid;
                bool          m_isRollCfgFileIsValid;
                WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // PERSISTENTWAVEBOOTAGENT_H
