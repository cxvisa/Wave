/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFAILOVERAGENT_H
#define PRISMFAILOVERAGENT_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include <vector>
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class PrismFailoverAgentSequencerContext;
class PrismFailoverAgentContext;

class PrismFailoverAgent : protected WaveWorker
{
    private :
        virtual bool           isToBeExcludedForFailover                    (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcludedDuringPrePhase                 (const WaveServiceId &waveServiceId);
        virtual bool           isToBeExcluded                               (const WaveServiceId &waveServiceId);
        virtual WaveBootReason getBootReason                                () const = 0;

        virtual FrameworkObjectManagerFailoverReason getFailoverReason      () const = 0;

                void           pausePersistence                             ();
                void           resumePersistence                            ();

    protected :
             PrismFailoverAgent                                             (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        void failoverPrismServicesStep                                      (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);

        void initializePrismGlobalServicesDuringPrePhaseStep                (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext); 
        void enablePrismGlobalServicesDuringPrePhaseStep                    (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void listenForEventsPrismGlobalServicesDuringPrePhaseStep           (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void bootPrismGlobalServicesDuringPrePhaseStep                      (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);

        void initializePrismGlobalServicesStep                              (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void enablePrismGlobalServicesStep                                  (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void listenForEventsPrismGlobalServicesStep                         (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void bootPrismGlobalServicesStep                                    (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);

        void createDatabaseDump                                             ();
        void pausePersistenceForPrimaryChangeStep                           (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryStep                    (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryCallback                (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void informSecondaryLocationsToChangePrimaryPhase1Step              (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase1Callback          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void resumeDatabaseDumpStep                                         (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase2Step              (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase2Callback          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void informSecondaryLocationsToChangePrimaryPhase3Step              (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase3Callback          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void removeOldPrimaryLocationStep                                   (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void resetThisLocationToPrimaryStep                                 (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void startHeartBeatToSecondariesStep                                (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void broadcastPrimaryChangedEventForPlugins                         (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void savePrismConfiguration                                         (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void informSecondaryLocationsToRemoveFailedFromKnownLocationsStep   (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void failoverForUnknownWaveNodePrismServicesStep                    (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);
        void backendSyncUpStep                                              (PrismFailoverAgentSequencerContext *pPrismFailoverAgentSequencerContext);

    public :
        virtual            ~PrismFailoverAgent                              ();
        virtual  void      execute                                          (PrismFailoverAgentContext *pPrismFailoverAgentContext);        

    // Now the data members

    private :
    protected :
        FrameworkSequenceGenerator &m_currentFrameworkSequenceGenerator;

    public :
};

}

#endif // PRISMFAILOVERAGENT_H
