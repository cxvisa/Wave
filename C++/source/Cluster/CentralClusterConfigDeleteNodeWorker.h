/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef CENTRALCLUSTERCONFIGDELETENODEWORKER_H
#define CENTRALCLUSTERCONFIGDELETENODEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs

{ 
class CentralClusterConfigObjectManager;
class ClusterObjectManagerDeleteNodeMessage;
class FrameworkObjectManagerDeleteNodesFromClusterMessage; 

class CentralClusterConfigDeleteNodeWorker : public WaveWorker {
    private :
                      CentralClusterConfigDeleteNodeWorker     (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager);

        WaveMessage *createMessageInstance                      (const UI32 &operationCode);
        void          deleteNodeMessageHandler                   (ClusterObjectManagerDeleteNodeMessage *pClusterObjectManagerDeleteNodeMessage);
        void          deleteNodeValidateStep                     (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          deleteNodeStopHeartBeatsStep               (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          deleteNodeRequestFrameworkToDeleteNodeStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);
        void          deleteNodeRequestFrameworkToDeleteNodeCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerDeleteNodesFromClusterMessage *pFrameworkObjectManagerDeleteNodesFromClusterMessage, void *pContext);

    protected :     
    public :

        ~CentralClusterConfigDeleteNodeWorker (); 
    // Now the data members

    private :
    protected :
    public :

    friend class CentralClusterConfigObjectManager;
};

}

#endif // CENTRALCLUSTERCONFIGADDNODEWORKER_H

