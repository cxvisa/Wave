/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Cluster/Local/HeartBeat/HeartBeatTypes.h"

namespace WaveNs
{

HeartBeatStat::HeartBeatStat ()
{
    m_heartBeatSent              = 0;
    m_heartBeatReplySent         = 0;
    m_lastHeartBeatReceived      = 0;
    m_heartBeatReceived          = 0;
    m_heartBeatLost              = 0;
    m_heartBeatLostInRow         = 0;
    m_heartBeatDelayed           = 0;
    m_heartBeatReplyReceived     = 0;
    m_lastHeartBeatReplyReceived = 0;
    m_heartBeatDuplicate         = 0;
}

HeartBeatStat::~HeartBeatStat ()
{
}

HeartBeatNodeInfo::HeartBeatNodeInfo ()
{
    m_heartBeatCurrentState  = 0;
    m_heartBeatFailureThreshold  = 0;
    m_heartBeatInterval  = 0;
    m_portNumber = 0;
    m_timerHandle = 0;
    m_waitingForHeartBeatReply = 0;
}

HeartBeatNodeInfo::~HeartBeatNodeInfo ()
{
}


}
