/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef HEARTBEATTYPES_H
#define HEARTBEATTYPES_H

#include "Framework/ObjectModel/WaveElement.h"

namespace WaveNs
{

#define                 DEFAULT_HEART_BEAT_PERIOD          10000
#define                 DEFAULT_MAX_LOST_HEARTBEATS        3

typedef enum
{
    HEARTBEAT_START = 0,
    HEARTBEAT_STOP,
    HEARTBEAT_PAUSE,
    HEARTBEAT_RESUME,
    HEARTBEAT_CONFIG,
    HEARTBEAT_REPORT,
    HEARTBEAT_GET_STAT,
    HEARTBEAT_SHOW_STAT,
    HEARTBEAT_LOST,
    HEARTBEAT_DISCONNECT_FROM_NODE

} HeartBeatOpCodes;

class HeartBeatStat
{
    private :
    protected :
    public :
        HeartBeatStat ();
        ~HeartBeatStat ();
         // Now the data members

    private :
    protected :
    public :

        UI32                      m_heartBeatSent;
        UI32                      m_heartBeatReplySent;
        
        UI32                      m_heartBeatReceived;
        UI32                      m_heartBeatReplyReceived;
        UI32                      m_lastHeartBeatReceived;
        UI32                      m_lastHeartBeatReplyReceived;
        
        UI32                      m_heartBeatLost;
        UI32                      m_heartBeatLostInRow;
        
        UI32                      m_heartBeatDelayed;
        UI32                      m_heartBeatDuplicate;

};

class HeartBeatNodeInfo
{
    private :
        HeartBeatNodeInfo ();

    protected :
    public :
        ~HeartBeatNodeInfo ();
         // Now the data members

    private :
        IpV4Address               m_ipAddress;
        UI16                      m_portNumber;
        UI8                       m_heartBeatCurrentState;
        UI32                      m_heartBeatInterval;
        UI32                      m_heartBeatFailureThreshold;
        UI8                       m_waitingForHeartBeatReply;
        TimerHandle               m_timerHandle;
        HeartBeatStat             m_heartBeatStat;


    protected :
    public :
        friend class HeartBeatObjectManager;
};

}

#endif //HEARTBEATTYPES_H
