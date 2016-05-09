/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEDISPATCHMESSAGE_H
#define LIGHTPULSEDISPATCHMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class LightPulseDispatchMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        LightPulseDispatchMessage     ();
        virtual        ~LightPulseDispatchMessage     ();

                string  getLightPulseSerializedString () const;
                void    setLightPulseSerializedString (const string &lightPulseSerializedString);

        // Now the data members

    private :
        string m_lightPulseSerializedString;

    protected :
    public :
};

}

#endif // LIGHTPULSEDISPATCHMESSAGE_H
