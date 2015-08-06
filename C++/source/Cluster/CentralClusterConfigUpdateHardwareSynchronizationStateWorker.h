/**
 *@file CentralClusterConfigUpdateHardwareSynchronizationStateWorker.h
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 * All rights reserved. 
 *
 * Description: This file declares the
 *              Worker class which is responsible for updating
 *              the hardware synchronization state attribute
 *              in the WaveNode Managed Object. 
 *
 * Author :     Brian Adaniya
 * Date :       05/13/2011
 */

#ifndef CENTRALCLUSTERCONFIGUPDATEHARDWARESYNCHRONIZATIONWORKER_H
#define CENTRALCLUSTERCONFIGUPDATEHARDWARESYNCHRONIZATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class CentralClusterConfigObjectManager;
class CentralClusterConfigUpdateHardwareSynchronizationStateMessage;
class WaveLinearSequencerContext;
class WaveSendToClusterContext;

class CentralClusterConfigUpdateHardwareSynchronizationStateWorker : public WaveWorker
{
    private :
                void            updateHardwareSynchronizationStateMessageHandler                (CentralClusterConfigUpdateHardwareSynchronizationStateMessage *pCentralClusterConfigUpdateHardwareSynchronizationStateMessage);
                void            sendUpdateWaveNodesToClusterLocalStep                           (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void            sendUpdateWaveNodesToClusterLocalStepCallback                   (WaveSendToClusterContext *pWaveSendToClusterContext);
                WaveMessage   *createMessageInstance                                           (const UI32 &operationCode);
    protected :
    public :
                                CentralClusterConfigUpdateHardwareSynchronizationStateWorker    (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager);
        virtual                ~CentralClusterConfigUpdateHardwareSynchronizationStateWorker    ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // CENTRALCLUSTERCONFIGUPDATEHARDWARESYNCHRONIZATIONWORKER_H
