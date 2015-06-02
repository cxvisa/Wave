/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PERSISTENTPRISMBOOTAGENT_H
#define PERSISTENTPRISMBOOTAGENT_H

#include "Framework/Boot/PrismBootAgent.h"

namespace WaveNs
{

class PersistentPrismBootAgent : public PrismBootAgent
{
    private :
        virtual bool           isAPersistentBoot                                          ();
        virtual WaveBootReason getReason                                                  () const;
        virtual bool           getRollBackFlag                                            () const;

                void           cleanPreparedTransactions                                  ();
                void           emptyDatabaseToRollBack                                    ();
                void           reloadPreviousDataBase                                     ();
//                void           rollbackCfgFile                                            ();

        virtual bool           isToBeExcludedForEnableAndBoot                             (const PrismServiceId& prismServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase                 (const PrismServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInitializePhase                          (const PrismServiceId &prismServiceId);

    protected :
    public :
                            PersistentPrismBootAgent                                   (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~PersistentPrismBootAgent                                   ();
        virtual ResourceId  execute                                                    (const WaveBootPhase &waveBootPhase);

                ResourceId  createFrameworkConfigurationFromPersistedConfigurationStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId  connectToKnownLocationsStep                                (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId  rollBackDataBase                                           (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId  resetLocationRole                                          (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
                ResourceId  disconnectFromAllConnectedLocations                        (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

    // Now the data members

    private :
                bool          m_isRollBackDataBaseValid;
                bool          m_isRollCfgFileIsValid;
                WaveBootPhase m_waveBootPhase;
    protected :
    public :
};

}

#endif // PERSISTENTPRISMBOOTAGENT_H
