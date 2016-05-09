/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEREGISTRATIONMESSAGE_H
#define LIGHTPULSEREGISTRATIONMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class LightPulseRegistrationMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        LightPulseRegistrationMessage ();
        virtual        ~LightPulseRegistrationMessage ();

                string  getLightPulseName             () const;
                void    setLightPulseName             (const string &lightPulseName);

        // Now the data members

    private :
        string m_lightPulseName;

    protected :
    public :
};

}

#endif // LIGHTPULSEREGISTRATIONMESSAGE_H
