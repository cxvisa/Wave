/**
 *@file ClusterLocalSetHardwareSynchronizationStateWorker.h
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 * All rights reserved. 
 *
 * Description: This file declares the
 *              Worker class which is responsible for updating
 *              the hardware synchronization state attribute
 *              in the WaveNode Managed Object. 
 *
 * Author :     Brian Adaniya
 * Date :       05/05/2011
 */

#ifndef CLUSTERLOCALSETHARDWARESYNCHRONIZATIONSTATEWORKER_H
#define CLUSTERLOCALSETHARDWARESYNCHRONIZATIONSTATEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterLocalObjectManager;
class ClusterLocalSetHardwareSynchronizationStateMessage;
class WaveLinearSequencerContext;

class ClusterLocalSetHardwareSynchronizationStateWorker : public WaveWorker
{
    private :
                void            setHardwareSynchronizationStateMessageHandler       (ClusterLocalSetHardwareSynchronizationStateMessage *pClusterLocalSetHardwareSynchronizationStateMessage);
                void            updateWaveNodeManagedObjectStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                WaveMessage   *createMessageInstance                               (const UI32 &operationCode);

    protected :
    public :
                                ClusterLocalSetHardwareSynchronizationStateWorker   (ClusterLocalObjectManager *pClusterLocalObjectManager);
        virtual                ~ClusterLocalSetHardwareSynchronizationStateWorker   ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CLUSTERLOCALSETHARDWARESYNCHRONIZATIONSTATEWORKER_H
