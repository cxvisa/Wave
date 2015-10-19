/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFAILOVERAGENT_H
#define WAVEFAILOVERAGENT_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include <vector>
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class WaveFailoverAgentSequencerContext;
class WaveFailoverAgentContext;

class WaveFailoverAgent : protected WaveWorker
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
             WaveFailoverAgent                                             (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        void failoverWaveServicesStep                                      (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);

        void initializeWaveGlobalServicesDuringPrePhaseStep                (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext); 
        void enableWaveGlobalServicesDuringPrePhaseStep                    (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void listenForEventsWaveGlobalServicesDuringPrePhaseStep           (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void bootWaveGlobalServicesDuringPrePhaseStep                      (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);

        void initializeWaveGlobalServicesStep                              (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void enableWaveGlobalServicesStep                                  (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void listenForEventsWaveGlobalServicesStep                         (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void bootWaveGlobalServicesStep                                    (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);

        void createDatabaseDump                                             ();
        void pausePersistenceForPrimaryChangeStep                           (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryStep                    (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryCallback                (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void informSecondaryLocationsToChangePrimaryPhase1Step              (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase1Callback          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void resumeDatabaseDumpStep                                         (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase2Step              (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase2Callback          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void informSecondaryLocationsToChangePrimaryPhase3Step              (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void informSecondaryLocationsToChangePrimaryPhase3Callback          (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);
        void removeOldPrimaryLocationStep                                   (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void resetThisLocationToPrimaryStep                                 (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void startHeartBeatToSecondariesStep                                (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void broadcastPrimaryChangedEventForPlugins                         (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void saveWaveConfiguration                                         (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void informSecondaryLocationsToRemoveFailedFromKnownLocationsStep   (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void failoverForUnknownWaveNodeWaveServicesStep                    (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);
        void backendSyncUpStep                                              (WaveFailoverAgentSequencerContext *pWaveFailoverAgentSequencerContext);

    public :
        virtual            ~WaveFailoverAgent                              ();
        virtual  void      execute                                          (WaveFailoverAgentContext *pWaveFailoverAgentContext);        

    // Now the data members

    private :
    protected :
        FrameworkSequenceGenerator &m_currentFrameworkSequenceGenerator;

    public :
};

}

#endif // WAVEFAILOVERAGENT_H
