/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CENTRALCLUSTERCONFIGADDNODEWORKER_H
#define CENTRALCLUSTERCONFIGADDNODEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{
class CentralClusterConfigObjectManager;
class ClusterObjectManagerAddNodeMessage;
class FrameworkObjectManagerAddNodesToClusterMessage;

class CentralClusterConfigAddNodeWorker : public WaveWorker
{
    private :
                      CentralClusterConfigAddNodeWorker        (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager);

        WaveMessage *createMessageInstance                    (const UI32 &operationCode);

        void          addNodeMessageHandler                    (ClusterObjectManagerAddNodeMessage *pClusterObjectManagerAddNodeMessage);
        void          addNodeValidateStep                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          addNodeRequestFrameworkToAddNodeStep     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          addNodeRequestFrameworkToAddNodeCallBack (FrameworkStatus frameworkStatus, FrameworkObjectManagerAddNodesToClusterMessage *pFrameworkObjectManagerAddNodesToClusterMessage, void *pContext);
        void          addNodeCommitStep                        (WaveLinearSequencerContext *pWaveLinearSequencerContex);
        void          addNodeStartHeartBeatsStep               (WaveLinearSequencerContext *pWaveLinearSequencerContext);
    protected :
    public :

        ~CentralClusterConfigAddNodeWorker ();

    // Now the data members

    private :
    protected :
    public :

    friend class CentralClusterConfigObjectManager;
};

}

#endif // CENTRALCLUSTERCONFIGADDNODEWORKER_H
