/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERTESTOBJECTMANAGER_H
#define CLUSTERTESTOBJECTMANAGER_H

#include "Cluster/Test/ClusterTestContexts.h"
#include "Regression/PrismTestObjectManager.h"
#include "Cluster/ClusterMessages.h"
#include <time.h>

namespace WaveNs
{
#define                 MAX_DUP_COMMAND_TRIALS      3
class ClusterTestData;

class ClusterTestObjectManager : public PrismTestObjectManager
{
    private :
                                ClusterTestObjectManager        ();
                    void        initBuffers                        ();
                    void        initData                        (ClusterTestContext *pClusterTestContext);
                    void        CreateDeleteClusterStep         (ClusterTestContext *pClusterTestContext);
                    void        DuplicateCmdStep                (ClusterTestContext *pClusterTestContext);
                    void        DuplicateCmdOneWayStep          (ClusterTestContext *pClusterTestContext);
                    void        DuplicateCmd                    (ClusterTestContext *pClusterTestContext, UI32 oneWay, UI32 multicast);
                    void        DuplicateCmdMulticastStep       (ClusterTestContext *pClusterTestContext);
                    void        DuplicateCmdMulticastOneWayStep (ClusterTestContext *pClusterTestContext);
                    void        AddDeleteNodeStep               (ClusterTestContext *pClusterTestContext);
                    void        ClusterShowStatStep             (ClusterTestContext *pClusterTestContext);
                    void        registerCallBacks               (ClusterTestContext *pClusterTestContext);
                    void        clusterCreateStep               (ClusterTestContext *pClusterTestContext);
                    void        clusterDeleteStep               (ClusterTestContext *pClusterTestContext);
    protected :
    public :
        virtual                          ~ClusterTestObjectManager ();
        static  ClusterTestObjectManager *getInstance              ();
        static  WaveServiceId            getWaveServiceId        ();
                void                      testRequestHandler       (RegressionTestMessage *pMessage);
        static  void                      duplicateCmdTestHandler  (void *pContext, unsigned int nCommands, commandData_t commandList []);
        static  void                      duplicateCmdTestReply    (int status, void * context, int nNodes, remoteCmdResult_t nodeResults []);
        void                              sendDuplicateCmd         (UI32 service, UI32 oneWay, UI32 multicast, duplicateCmdResultCallBack_t duplicateCmdResultCB, void *pContext);
        static  void                      duplicateCmdReply        (int status, void * context, int nNodes, remoteCmdResult_t nodeResults []);
    // Now the data members

    private :

    protected :
    public :
        UI32        nDupCommandTrials;
};

class ClusterTestData
{
    private :
    protected :
    public :
                    ClusterTestData             ();
                   ~ClusterTestData             ();
        // Now the data members

    private :
    protected :
    public :
                    ClusterTestContext      *m_pClusterTestContext;

};


}

#endif // CLUSTERTESTOBJECTMANAGER_H
