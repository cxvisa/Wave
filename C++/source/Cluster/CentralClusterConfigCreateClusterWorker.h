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
class WaveCreateClusterWithNodesMessage;

class CentralClusterConfigCreateClusterWorker : public WaveWorker
{
    private :
                      CentralClusterConfigCreateClusterWorker              (WaveObjectManager *pWaveObjectManager);

        WaveMessage *createMessageInstance                                (const UI32 &operationCode);

        void          createClusterMessageHandler                          (ClusterObjectManagerCreateClusterMessage *pClusterObjectManagerCreateClusterMessage);
        void          createClusterValidateStep                            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          createClusterResetThisNodeIpAddressIfRequiredStep    (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          createClusterRequestFrameworkToCreateClusterStep     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          createClusterRequestFrameworkToCreateClusterCallback (FrameworkStatus frameworkStatus, WaveCreateClusterWithNodesMessage *pWaveCreateClusterWithNodesMessage, void *pContext);
        void          createClusterCommitStep                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          createClusterStartHeartBeatsStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);

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
