/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGOBJECTMANAGER_H
#define DISTRIBUTEDLOGOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class DistributedLogAddLogEntryMessage;
class DistributedLogUpdateMaxLogEntriesMessage;
class DistributedLogSynchronousLinearSequencerContext;
class DistributedLogConfigurationManagedObject;
class DistributedLogUpdateLogIdMessage;

class DistributedLogObjectManager : public WaveObjectManager
{
    private :
                void                            initialize                                                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                            install                                                     (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                            haboot                                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                ResourceId                      distributedLogInstallDefaultConfigurationMOStep             (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);
                ResourceId                      distributedLogUpdateInMemoryObjectsFromConfigurationMOStep  (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);
                ResourceId                      distributedLogUpdateInMemoryObjectsFromEntriesMOStep        (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);

                void                            distributedLogAddLogEntryMessageHandler                     (DistributedLogAddLogEntryMessage *pDistributedLogAddLogEntryMessage);
                void                            distributedLogUpdateMaxLogEntriesMessageHandler             (DistributedLogUpdateMaxLogEntriesMessage *pDistributedLogUpdateMaxLogEntriesMessage);
                void                            distributedLogUpdateInMemoryLogIdMessageHandler             (DistributedLogUpdateLogIdMessage *pDistributedLogUpdateLogIdMessage);

                ResourceId                      distributedLogSetupADelayedCommitTransactionIfRequiredStep  (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);
                ResourceId                      distributedLogAddLogEntryStep                               (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);
                ResourceId                      distributedLogUpdateFirstAndNextLogIdStep                   (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);
                ResourceId                      distributedLogRemoveLogEntriesIfRequiredStep                (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);
                ResourceId                      distributedLogUpdateMaxLogEntriesStep                       (DistributedLogSynchronousLinearSequencerContext *pDistributedLogSynchronousLinearSequencerContext);

                UI64                            getNumberOfLogEntries                                       () const; 
                bool                            isLogEmpty                                                  () const;
                bool                            isLogFull                                                   () const;

        static  ResourceId                      distributedLogAddLogEntryDebugHandler                       (UI32 argc, vector<string> argv);
        static  ResourceId                      distributedLogUpdateMaxLogEntriesDebugHandler               (UI32 argc, vector<string> argv);
                void                            dbInconsistencyCheck                                        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

    protected :
    public :
                                                DistributedLogObjectManager                                 ();
        virtual                                ~DistributedLogObjectManager                                 ();

        virtual WaveMessage                   *createMessageInstance                                       (const UI32 &operationCode);
                WaveManagedObject              *createManagedObjectInstance                                 (const string &managedClassName);

        static  string                          getServiceName                                              ();
        static  DistributedLogObjectManager    *getInstance                                                 ();
        static  WaveServiceId                  getWaveServiceId                                           ();

    // Now the data members

    private :
        UI64                                        m_maxLogEntries;
        UI64                                        m_firstLogId;
        UI64                                        m_nextLogId;

    protected :
    public :
};

}

#endif // DISTRIBUTEDLOGOBJECTMANAGER_H
