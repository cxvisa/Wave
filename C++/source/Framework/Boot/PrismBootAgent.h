/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMBOOTAGENT_H
#define PRISMBOOTAGENT_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
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

class PrismBootAgent : protected WaveWorker
{
    private :
        virtual bool           isAPersistentBoot                            ();
        virtual bool           isToBeExcludedForEnableAndBoot               (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInstallDuringPrePhase      (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInstall                    (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromCurrentBootPhase           (WaveServiceId prismServiceId);
        virtual bool           isToBeExcludedFromInitializeDuringPrePhase   (const WaveServiceId &prismServiceId);
        virtual bool           isToBeExcludedFromInitializePhase            (const WaveServiceId &prismServiceId);

        virtual WaveBootReason getReason                                    () const;
        virtual bool           getRollBackFlag                              () const;
        void                   handleUpgradeFailure                         (const WaveServiceId& service);

    protected :
                   PrismBootAgent                                 (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        void       addAStepToPrismBootAgent                       (PrismSynchronousLinearSequencerStep prismBootAgentStep);
        virtual bool           willBeAPrimaryLocation                       ();

        ResourceId initializePrismServicesDuringPrePhaseStep      (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId listenForEventsPrismServicesDuringPrePhaseStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId enablePrismServicesDuringPrePhaseStep          (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId upgradePrismServicesDuringPrePhaseStep         (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId installPrismServicesDuringPrePhaseStep         (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId bootPrismServicesDuringPrePhaseStep            (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

        ResourceId initializeGlobalPrismServicesDuringPrePhaseStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId listenForEventsGlobalServicesDuringPrePhaseStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId enableGlobalPrismServicesDuringPrePhaseStep     (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId upgradeGlobalPrismServicesDuringPrePhaseStep    (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId bootGlobalPrismServicesDuringPrePhaseStep       (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

        ResourceId initializeLocalPrismServicesStep               (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId listenForEventsLocalPrismServicesStep          (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId enableLocalPrismServicesStep                   (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId upgradeLocalPrismServicesStep                  (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId installLocalPrismServicesStep                  (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId bootLocalPrismServicesStep                     (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

        ResourceId initializeGlobalPrismServicesStep              (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId listenForEventsGlobalPrismServicesStep         (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId enableGlobalPrismServicesStep                  (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId upgradeGlobalPrismServicesStep                 (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId installGlobalPrismServicesStep                 (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId bootGlobalPrismServicesStep                    (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

        ResourceId initializePrismServicesStep                    (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId listenForEventsPrismServicesStep               (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId enablePrismServicesStep                        (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId upgradePrismServicesStep                       (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId installPrismServicesStep                       (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId bootPrismServicesStep                          (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

        ResourceId updateDatabaseForeignKeyConstraintsStep        (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId databaseSanityCheckStep                        (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
        ResourceId updateUserDefinedKeyCombinationConstraintsAndKeysStep (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

        ResourceId backendSyncUpStep                              (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

    public :
        virtual            ~PrismBootAgent ();
        virtual ResourceId  execute        (const WaveBootPhase &waveBootPhase);

    // Now the data members

    private :
    protected :
        FrameworkSequenceGenerator &m_currentFrameworkSequenceGenerator;

    public :
};

}

#endif // PRISMBOOTAGENT_H
