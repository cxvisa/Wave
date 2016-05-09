/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEUNREGISTRATIONMESSAGE_H
#define LIGHTPULSEUNREGISTRATIONMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class LightPulseUnregistrationMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        LightPulseUnregistrationMessage ();
                        LightPulseUnregistrationMessage (const string &lightPulseName);
        virtual        ~LightPulseUnregistrationMessage ();

                string  getLightPulseName               () const;
                void    setLightPulseName               (const string &lightPulseName);

        // Now the data members

    private :
        string m_lightPulseName;

    protected :
    public :
};

}

#endif // LIGHTPULSEUNREGISTRATIONMESSAGE_H
