/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETRANSPORTBROADCASTLIGHTPULSEWORKER_H
#define LIGHTHOUSETRANSPORTBROADCASTLIGHTPULSEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class LightHouseTransportObjectManager;
class LightHouseTransportBroadcastLightPulseMessage;
class MulticastSenderSocket;

class LightHouseTransportBroadcastLightPulseWorker : public WaveWorker
{
    private :
        void broadcastLightPulseMessageHandler (LightHouseTransportBroadcastLightPulseMessage *pLightHouseTransportBroadcastLightPulseMessage);

    protected :
    public :
                 LightHouseTransportBroadcastLightPulseWorker (LightHouseTransportObjectManager *pLightHouseTransportObjectManager);
        virtual ~LightHouseTransportBroadcastLightPulseWorker ();

        // Now the data members

    private :
        MulticastSenderSocket *m_pMulticastSenderSocket;

    protected :
    public :
};

}

#endif // LIGHTHOUSETRANSPORTBROADCASTLIGHTPULSEWORKER_H
