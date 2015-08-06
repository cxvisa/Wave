/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                   *
 ***************************************************************************/

#ifndef CENTRALCLUSTERCONFIGREJOINNODEWORKER_H
#define CENTRALCLUSTERCONFIGREJOINNODEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{
class CentralClusterConfigObjectManager;
class ClusterObjectManagerRejoinNodeMessage;
class FrameworkObjectManagerRejoinNodesToClusterMessage;
class ClusterRejoinContext;

class CentralClusterConfigRejoinNodeWorker : public WaveWorker
{
    private :
                      CentralClusterConfigRejoinNodeWorker        (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager);

virtual WaveMessage *createMessageInstance                       (const UI32 &operationCode);

        void          rejoinNodeMessageHandler                    (ClusterObjectManagerRejoinNodeMessage *pClusterObjectManagerRejoinNodeMessage);
        void          rejoinNodeValidateStep                      (ClusterRejoinContext *pClusterRejoinContext);
        void          rejoinNodeRequestFrameworkToRejoinNodeStep  (ClusterRejoinContext *pClusterRejoinContext);
        void          rejoinNodeRequestFrameworkToRejoinNodeCallBack (FrameworkStatus frameworkStatus, FrameworkObjectManagerRejoinNodesToClusterMessage *  pFrameworkObjectManagerRejoinNodesToClusterMessage, void *pContext);
        void          rejoinNodeCommitStep                        (ClusterRejoinContext *pClusterRejoinContext);
        void          rejoinNodeStartHeartBeatsStep               (ClusterRejoinContext *pClusterRejoinContext);
    protected :
    public :

    virtual    ~CentralClusterConfigRejoinNodeWorker ();

    // Now the data members

    private :
    protected :
    public :

    friend class CentralClusterConfigObjectManager;
};

}

#endif // CENTRALCLUSTERCONFIGREJOINNODEWORKER_H
