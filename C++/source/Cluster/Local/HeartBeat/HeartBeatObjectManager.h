/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef HEARTBEATOBJECTMANAGER_H
#define HEARTBEATOBJECTMANAGER_H

#include "App/AppInterface.h"
#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"
#include "Cluster/Local/HeartBeat/HeartBeatMessages.h"
#include "Cluster/Local/HeartBeat/HeartBeatDebug.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForShutdownPhases.h"
#include <string>
#include <vector>

namespace WaveNs
{
class HeartBeatNodeInfo;
class HeartBeatConfigLocalManagedObject;

class HeartBeatObjectManager : public WaveLocalObjectManager
{
    private :
                                        HeartBeatObjectManager      ();
        virtual WaveMessage           *createMessageInstance       (const UI32 &operationCode);
                WaveManagedObject      *createManagedObjectInstance (const string &managedClassName);
                void                    setThisLocationIpAddr       (const string &thisLocationIpAddr);
    protected :
    public :
        virtual                        ~HeartBeatObjectManager      ();
        static  HeartBeatObjectManager *getInstance                 ();
        static  WaveServiceId          getWaveServiceId           ();

                void                    initialize                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                    install                     (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                    shutdown                    (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);

                void                    startHeartBeat              (StartHeartBeatMessage *pMessage);
                void                    stopHeartBeat               (StopHeartBeatMessage *pMessage);
                void                    pauseHeartBeat              (PauseHeartBeatMessage *pMessage);
                void                    resumeHeartBeat             (ResumeHeartBeatMessage *pMessage);
                void                    configHeartBeat             (ConfigHeartBeatMessage *pMessage);
                void                    reportHeartBeat             (ReportHeartBeatMessage *pMessage);
                void                    processHeartBeatReply       (FrameworkStatus frameworkStatus, ReportHeartBeatMessage *pMessage, HeartBeatNodeInfo *pHeartBeatInfo);
                void                    heartBeatTimerHandler       (TimerHandle timerHandle, HeartBeatNodeInfo *pHeartBeatInfo);
                void                    sendHeartBeat               (HeartBeatNodeInfo *pHeartBeatInfo);

                void                    getHeartBeatStat            (GetHeartBeatStatMessage *pMessage);
                void                    showHeartBeatStat           (ShowHeartBeatStatMessage *pMessage);
                void                    showStatistic               (ShowHeartBeatStatMessage *pMessage);

                void                    disconnectFromNodeMessageHandler    (DisconnectFromNodeMessage *pDisconnectFromNodeMessage);
                void                    validateDisconnectFromNodeRequest   (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void                    processDisconnectFromNodeMessage    (PrismLinearSequencerContext *pPrismLinearSequencerContext);

                
                
                HeartBeatConfigLocalManagedObject *getConfigManagedObjectInstance (); 

        // Now the data members

    private :
                IpV4Address                  m_thisLocationIpAddr;
                UI16                         m_thisLocationPort;
                vector <HeartBeatNodeInfo *> m_heartBeatNodes;
                HeartBeatDebug               m_heartBeatDebug;


    protected :
    public :

    friend class LocalClusterConfigObjectManager;
};

}

#endif // HEARTBEATBJECTMANAGER_H
