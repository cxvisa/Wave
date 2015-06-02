/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CENTRALCLUSTERCONFIGCREATECLUSTERWORKER_H
#define CENTRALCLUSTERCONFIGCREATECLUSTERWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class ClusterObjectManagerCreateClusterMessage;
class PrismCreateClusterWithNodesMessage;

class CentralClusterConfigCreateClusterWorker : public WaveWorker
{
    private :
                      CentralClusterConfigCreateClusterWorker              (WaveObjectManager *pWaveObjectManager);

        PrismMessage *createMessageInstance                                (const UI32 &operationCode);

        void          createClusterMessageHandler                          (ClusterObjectManagerCreateClusterMessage *pClusterObjectManagerCreateClusterMessage);
        void          createClusterValidateStep                            (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void          createClusterResetThisNodeIpAddressIfRequiredStep    (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void          createClusterRequestFrameworkToCreateClusterStep     (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void          createClusterRequestFrameworkToCreateClusterCallback (FrameworkStatus frameworkStatus, PrismCreateClusterWithNodesMessage *pPrismCreateClusterWithNodesMessage, void *pContext);
        void          createClusterCommitStep                              (PrismLinearSequencerContext *pPrismLinearSequencerContext);
        void          createClusterStartHeartBeatsStep                     (PrismLinearSequencerContext *pPrismLinearSequencerContext);

    protected :
    public :
        ~CentralClusterConfigCreateClusterWorker ();

    // Now the data members

    private :
    protected :
    public :

    friend class CentralClusterConfigObjectManager;
};

}

#endif // CENTRALCLUSTERCONFIGCREATECLUSTERWORKER_H
