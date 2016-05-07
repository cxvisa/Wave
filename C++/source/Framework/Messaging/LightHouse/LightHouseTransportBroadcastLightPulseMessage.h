/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETRANSPORTBROADCASTLIGHTPULSEMESSAGE_H
#define LIGHTHOUSETRANSPORTBROADCASTLIGHTPULSEMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class LightPulse;

class LightHouseTransportBroadcastLightPulseMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                            LightHouseTransportBroadcastLightPulseMessage (LightPulse *pLightPulse);
        virtual            ~LightHouseTransportBroadcastLightPulseMessage ();

                LightPulse *getPLightPulse                                ();

        // Now the data members

    private :
        LightPulse *m_pLightPulse;

    protected :
    public :
};

}

#endif // LIGHTHOUSETRANSPORTBROADCASTLIGHTPULSEMESSAGE_H

