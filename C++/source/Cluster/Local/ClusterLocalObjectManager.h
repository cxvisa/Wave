/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERLOCALOBJECTMANAGER_H
#define CLUSTERLOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/Utils/WaveMutex.h"
#include "Cluster/Local/WaveNode.h"
#include "Cluster/Local/WaveHaNodeTypes.h"
#include "Framework/Core/WaveNewNodesAddedEvent.h"
#include "Framework/Core/ClusterPhase3StartEvent.h"
#include "Framework/Core/ClusterPhase3CompleteEvent.h"
#include "Cluster/Local/WaveSlotLocalManagedObject.h"
#include "Cluster/Local/ClusterLocalGetObjectIdMessages.h"

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;
class WaveAsynchronousContextForShutDownPhases;
class WaveSynchronousLinearSequencerContext;
class ClusterLocalSetThisNodeIpAddressWorker;
class ClusterLocalReportPrimaryNodeChangedWorker;
class ClusterLocalReportRemovedNodeFromClusterWorker;
class ClusterLocalReportReplaceWorker;
class ClusterLocalSetHardwareSynchronizationStateWorker;
class ClusterLocalSetHaRoleWorker;
class ClusterLocalWaveSlotManagementWorker;
class ClusterLocalGetObjectIdWorker;
class CliBlockServiceIndependentMessage;
class ClusterLocalSetControllerDetailsMessage;
class ClusterLocalReportToControllerAsClientMessage;

class ClusterLocalObjectManager : public WaveLocalObjectManager
{
    private :
                           ClusterLocalObjectManager                        ();

        WaveManagedObject *createManagedObjectInstance                      (const string &managedClassName);

		//WaveMessage 	  *createMessageInstance (const UI32 &operationCode);

        void               install                                          (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void               boot                                             (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        void               shutdown                                         (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
        void               backendSyncUp                                    (WaveAsynchronousContext *pWaveAsynchronousContext);

        void               setThisWaveNodeObjectId                          (const ObjectId &thisWaveNodeObjectId);

        WaveNode*          getThisWaveNodeManagedObject                     ();

        void               setThisWaveHaNodeRole                            (const WaveHaNodeRole &thisWaveHaNodeRole);

        void               nodeAddedEventHandler                            (const WaveNewNodesAddedEvent* &pEvent);

        void               phase3StartEventHandler                          (const ClusterPhase3StartEvent* &pEvent );

        void               phase3CompleteEventHandler                       (const ClusterPhase3CompleteEvent* &pEvent );

        void               listenForEvents                                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        void               setControllerDetailsMessageHandler               (ClusterLocalSetControllerDetailsMessage *pClusterLocalSetControllerDetailsMessage);
        void               clientReportingToControllerMessageHandler        (ClusterLocalReportToControllerAsClientMessage *pClusterLocalReportToControllerAsClientMessage);
        void               clusterLocalReportToControllerAsClientCallback   (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void *pContext);

        void               controllerClusterFormationDampeningTimerCallback (TimerHandle &timerHandle, void *pContext);

    protected :
    public :
        virtual                           ~ClusterLocalObjectManager        ();

        static  ClusterLocalObjectManager *getInstance                      ();
        static  WaveServiceId             getWaveServiceId                ();
        static  string                     getWaveServiceName              ();

        static  bool                       getIsInstantiated                ();

        ObjectId                   		   getThisWaveNodeObjectId          ();

        WaveHaNodeRole                     getThisWaveHaNodeRole            ();
        void                               haboot                           (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                               dbInconsistencyCheck             (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void                               cliBlockMessageHandler           (CliBlockServiceIndependentMessage *pCliBlockServiceIndependentMessage);
        static  void                       cliBlockMessageStaticHandler     (CliBlockServiceIndependentMessage *pCliBlockServiceIndependentMessage);
        virtual WaveMessage*              createMessageInstance            (const UI32 &operationCode);
        virtual ResourceId                 blockCli                         (const ResourceId &reason, const bool &clusterWide);
        virtual ResourceId                 unblockCli                       (const ResourceId &reason, const bool &clusterWide);


    // Now the Data Members

    private :
               ObjectId                                             m_thisWaveNodeObjectId;
               WaveMutex                                           m_thisWaveNodeObjectIdMutex;

               WaveHaNodeRole                                       m_thisWaveHaNodeRole;
               WaveMutex                                           m_thisWaveHaNodeRoleMutex;
               IpVxAddress                                          m_thisWaveNodeControllerIpAddress;
               SI32                                                 m_thisWaveNodeControllerPort;
        static UI32                                                 m_thisNodeClientIndentificationNumber;
        static bool                                                 m_isInstantiated;
        static vector<IpVxAddress>                                  m_pendingIpaddressesToBeAddedToController;
        static vector<SI32>                                         m_pendingPortsToBeAddedToController;
        static TimerHandle                                          m_controllerClusterFormationDampeningTimerHandle;
               ResourceId                                           m_thisHardwareSyncState;

               ClusterLocalSetThisNodeIpAddressWorker              *m_pClusterLocalSetThisNodeIpAddressWorker;
    	       ClusterLocalReportPrimaryNodeChangedWorker          *m_pClusterLocalPrimaryNodeChangedWorker;
	           ClusterLocalReportRemovedNodeFromClusterWorker      *m_pClusterLocalReportRemovedNodeFromClusterWorker;
               ClusterLocalReportReplaceWorker                     *m_pClusterLocalReportReplaceWorker;
               ClusterLocalSetHardwareSynchronizationStateWorker   *m_pClusterLocalSetHardwareSynchronizationStateWorker;
               ClusterLocalSetHaRoleWorker                         *m_pClusterLocalSetHaRoleWorker;
		       ClusterLocalWaveSlotManagementWorker                *m_pClusterLocalWaveSlotManagementWorker;
               ClusterLocalGetObjectIdWorker                       *m_pClusterLocalGetObjectIdWorker;

    protected :
    public :

    friend  class ClusterLocalSetHardwareSynchronizationStateWorker;
	friend  class ClusterLocalWaveSlotManagementWorker;
};

}

#endif // CLUSTERLOCALOBJECTMANAGER_H

