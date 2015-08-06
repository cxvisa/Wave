/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HEARTBEATFAILUREAGENT_H
#define HEARTBEATFAILUREAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class HeartBeatFailureAgentContext;

class HeartBeatFailureAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            HeartBeatFailureAgent                (WaveObjectManager *pWaveObjectManager, IpV4Address ipAddress, UI16 portNumber);
        virtual            ~HeartBeatFailureAgent                ();
        virtual ResourceId  execute                              ();

                ResourceId  getListOfEnabledServicesStep         (HeartBeatFailureAgentContext *pHeartBeatFailureAgentContext);
                ResourceId  sendHeartBeatFailureStep             (HeartBeatFailureAgentContext *pHeartBeatFailureAgentContext);

                bool        requiresHeartBeatFailureNotification (const WaveServiceId &prismServiceId);

    // Now the data members

    private :
		IpV4Address m_ipAddress;
		UI16        m_portNumber;
    protected :
    public :
};

}

#endif // HeartBeatFailureAgent_H
