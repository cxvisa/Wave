/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETESTLIGHTPULSE1_H
#define LIGHTHOUSETESTLIGHTPULSE1_H

#include "Framework/Messaging/LightHouse/LightPulse.h"

using WaveNs::LightPulse;

namespace WaveNs
{

class LightHouseTestLightPulse1 : public LightPulse
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                       LightHouseTestLightPulse1 ();
        virtual       ~LightHouseTestLightPulse1 ();

        static string  getLightPulseName         ();

               string  getLightMessage           () const;
               void    setLightMessage           (const string &lightMessage);

        // Now the data members

    private :
        string m_lightMessage;

    protected :
    public :
};

}

#endif // LIGHTHOUSETESTLIGHTPULSE1_H
