/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGTESTOBJECTMANAGER_H
#define DISTRIBUTEDLOGTESTOBJECTMANAGER_H

#include "Regression/PrismTestObjectManager.h"

namespace WaveNs
{

class DistributedLogInvokeAddLogApiMessage;
class DistributedLogTestContext;

class DistributedLogTestObjectManager : public PrismTestObjectManager
{
    private :
        virtual WaveMessage                       *createMessageInstance                                   (const UI32 &operationCode);
                void                                invokeAddLogApiMessageHandler                           (DistributedLogInvokeAddLogApiMessage *pMessage);
                void                                testRequestHandler                                      (RegressionTestMessage *pMessage);
                void                                dumpAndSaveOriginalStatsTestStep                        (DistributedLogTestContext *pDistributedLogTestContext);
                void                                queryForCurrentConfigInfoTestStep                       (DistributedLogTestContext *pDistributedLogTestContext);
                void                                addMaximumLogEntriesTestStep                            (DistributedLogTestContext *pDistributedLogTestContext);
                void                                verifyMaximumLogEntriesTestStep                         (DistributedLogTestContext *pDistributedLogTestContext);
                void                                rotateLogEntriesTestStep                                (DistributedLogTestContext *pDistributedLogTestContext);
                void                                verifyRotatedLogEntriesTestStep                         (DistributedLogTestContext *pDistributedLogTestContext);
                void                                decreaseMaxAllowedLogEntriesTestStep                    (DistributedLogTestContext *pDistributedLogTestContext);
                void                                verifyDecreasedLogEntriesTestStep                       (DistributedLogTestContext *pDistributedLogTestContext);
                void                                increaseMaxAllowedLogEntriesTestStep                    (DistributedLogTestContext *pDistributedLogTestContext);
                void                                verifyUnchangedLogEntriesTestStep                       (DistributedLogTestContext *pDistributedLogTestContext);
                void                                addMaximumLogEntriesUsingSendOneWayApiTestStep          (DistributedLogTestContext *pDistributedLogTestContext);
                void                                addAuditLog1UsingSendToWaveClusterTestStep              (DistributedLogTestContext *pDistributedLogTestContext);
                void                                addAuditLog2UsingSendToWaveClusterTestStep              (DistributedLogTestContext *pDistributedLogTestContext);
                void                                addAuditLog3UsingSendToWaveClusterTestStep              (DistributedLogTestContext *pDistributedLogTestContext);
                void                                addManagedObjectLog1UsingSendToWaveClusterTestStep      (DistributedLogTestContext *pDistributedLogTestContext);
                void                                addLogUsingSendToWaveClusterTestCallback                (WaveSendToClusterContext *pWaveSendToClusterContext);
                void                                restoreMaxAllowedLogEntriesTestStep                     (DistributedLogTestContext *pDistributedLogTestContext);

                ResourceId                          queryForNumberOfLogEntries                              (UI64 &numberOfLogEntries); 
                ResourceId                          queryForFirstLogId                                      (UI64 &firstLogId); 
                ResourceId                          queryForLastLogId                                       (UI64 &lastLogId); 
                ResourceId                          queryForLogEntryInformation                             (UI64 &count, UI64 &firstLogId, UI64 &lastLogId);

    protected :
    public :
                                                    DistributedLogTestObjectManager                         ();
        virtual                                    ~DistributedLogTestObjectManager                         ();

        static  string                              getServiceName                                          ();
        static  DistributedLogTestObjectManager    *getInstance                                             ();
        static  WaveServiceId                      getWaveServiceId                                       ();


    // Now the data members

    private :
    protected :
    public :

};

} 

#endif // DISTRIBUTEDLOGTESTOBJECTMANAGER_H
