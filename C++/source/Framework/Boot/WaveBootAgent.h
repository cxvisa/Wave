/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBOOTAGENT_H
#define WAVEBOOTAGENT_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

#include <vector>

using namespace std;

namespace WaveNs
{

typedef enum
{
    WAVE_BOOT_PHASE_PRE_PHASE                     = 0,
    WAVE_BOOT_PHASE_POST_PHASE                    = 1,
    WAVE_BOOT_PHASE_AFTER_POST_PHASE              = 2,
    WAVE_BOOT_ROLL_BACK_BOOT_PHASE                = 3,    
    WAVE_BOOT_ROLL_BACK_BOOT_PHASE_AFTER_PHASE_2  = 4,
    WAVE_BOOT_RESET_NODE_TO_UNCONFIRM_ROLE        = 5,
    WAVE_BOOT_ROLL_BACK_BOOT_PHASE_BEFORE_PHASE_0 = 6,
    WAVE_BOOT_PREPARE_FOR_HA_FAILOVER_PHASE       = 7,
    WAVE_BOOT_PHASE_ALL_PHASES 
} WaveBootPhase;

class WaveBootAgent : protected WaveWorker
{
    private :
        virtual bool           isAPersistentBoot                            ();
        virtual bool           isToBeExcludedForEnableAndBoot               (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInstall                    (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (WaveServiceId waveServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const WaveServiceId &waveServiceId);

        virtual WaveBootReason getReason                                    () const;
        virtual bool           getRollBackFlag                              () const;
        void                   handleUpgradeFailure                         (const WaveServiceId& service);

    protected :
                   WaveBootAgent                                 (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        void       addAStepToWaveBootAgent                       (WaveSynchronousLinearSequencerStep prismBootAgentStep);
        virtual bool           willBeAPrimaryLocation                       ();

        ResourceId initializeWaveServicesDuringPrePhaseStep      (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId listenForEventsWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId enableWaveServicesDuringPrePhaseStep          (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId upgradeWaveServicesDuringPrePhaseStep         (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId installWaveServicesDuringPrePhaseStep         (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId bootWaveServicesDuringPrePhaseStep            (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

        ResourceId initializeGlobalWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId listenForEventsGlobalServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId enableGlobalWaveServicesDuringPrePhaseStep     (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId upgradeGlobalWaveServicesDuringPrePhaseStep    (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId bootGlobalWaveServicesDuringPrePhaseStep       (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

        ResourceId initializeLocalWaveServicesStep               (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId listenForEventsLocalWaveServicesStep          (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId enableLocalWaveServicesStep                   (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId upgradeLocalWaveServicesStep                  (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId installLocalWaveServicesStep                  (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId bootLocalWaveServicesStep                     (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

        ResourceId initializeGlobalWaveServicesStep              (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId listenForEventsGlobalWaveServicesStep         (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId enableGlobalWaveServicesStep                  (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId upgradeGlobalWaveServicesStep                 (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId installGlobalWaveServicesStep                 (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId bootGlobalWaveServicesStep                    (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

        ResourceId initializeWaveServicesStep                    (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId listenForEventsWaveServicesStep               (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId enableWaveServicesStep                        (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId upgradeWaveServicesStep                       (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId installWaveServicesStep                       (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId bootWaveServicesStep                          (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

        ResourceId updateDatabaseForeignKeyConstraintsStep        (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId databaseSanityCheckStep                        (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
        ResourceId updateUserDefinedKeyCombinationConstraintsAndKeysStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

        ResourceId backendSyncUpStep                              (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

    public :
        virtual            ~WaveBootAgent ();
        virtual ResourceId  execute        (const WaveBootPhase &waveBootPhase);

    // Now the data members

    private :
    protected :
        FrameworkSequenceGenerator &m_currentFrameworkSequenceGenerator;

    public :
};

}

#endif // WAVEBOOTAGENT_H
