/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGER_H
#define WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage;
class WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage;

class WaveMessagingBrokerConnectionObjectManager : public WaveLocalObjectManager
{
    private :
        bool isAKnownWaveMessagingBroker                   (const string &waveMesagingBrokerName);
        void requestToTryForConnectionMessageHandler       (WaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage       *pWaveMessagingBrokerConnectionObjectManagerRequestToTryForConnectionMessage);
        void cancelRequestToTryForConnectionMessageHandler (WaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage *pWaveMessagingBrokerConnectionObjectManagerCancelRequestToTryForConnectionMessage);

        void startTimerIfNeeded                            ();

        void timerCallback                                 (TimerHandle timeHandle, void *pContext);

        void removeWaveMessagingBrokerNameFromPendingList  (const string &waveMessagingBrokerName);

    protected :
    public :
                                                            WaveMessagingBrokerConnectionObjectManager ();
        virtual                                            ~WaveMessagingBrokerConnectionObjectManager ();

        static  string                                      getServiceName                             ();
        static  PrismServiceId                              getPrismServiceId                          ();
        static  WaveMessagingBrokerConnectionObjectManager *getInstance                                ();

    // Now the data members

    private :
        map<string, string> m_pendingWaveMessagingBrokerNamesToTryForConnection;
        UI32                m_tryIntervalInMilliSeconds;
        TimerHandle         m_timerHandle;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERCONNECTIONOBJECTMANAGER_H
