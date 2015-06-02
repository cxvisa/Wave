                                                                                                                                                                           /***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CENTRALCLUSTERCONFIGDELETECLUSTERWORKER_H
#define CENTRALCLUSTERCONFIGDELETECLUSTERWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class FrameworkObjectManagerDestroyClusterMessage;
class ClusterDeleteContext;
class ClusterObjectManagerDeleteClusterMessage;

class CentralClusterConfigDeleteClusterWorker : public WaveWorker
{
    private :
                      CentralClusterConfigDeleteClusterWorker              (WaveObjectManager *pWaveObjectManager);

        PrismMessage *createMessageInstance                                (const UI32 &operationCode);

        void          deleteClusterMessageHandler                          (ClusterObjectManagerDeleteClusterMessage *pClusterObjectManagerDeleteClusterMessage);
        void          deleteClusterValidateStep                            (ClusterDeleteContext *pClusterDeleteContext);
        void          deleteClusterStopHeartBeatsStep                      (ClusterDeleteContext *pClusterDeleteContext);
        void          deleteClusterRequestFrameworkToDeleteClusterStep     (ClusterDeleteContext *pClusterDeleteContext);
        void          deleteClusterRequestFrameworkToDeleteClusterCallback (FrameworkStatus frameworkStatus, FrameworkObjectManagerDestroyClusterMessage *pFrameworkObjectManagerDestroyClusterMessage, void *pContext);
        void          deleteClusterCommitStep                              (ClusterDeleteContext *pClusterDeleteContext);

    protected :
    public :
        ~CentralClusterConfigDeleteClusterWorker ();

    // now the data members

    private :
    protected :
    public :

    friend class CentralClusterConfigObjectManager;
};

}

#endif // CENTRALCLUSTERCONFIGDELETECLUSTERWORKER_H
