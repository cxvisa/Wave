/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETESTOBJECTMANAGER2_H
#define LIGHTHOUSETESTOBJECTMANAGER2_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class RegressionTestMessage;

class LightHouseTestObjectManager2 : public WaveLocalObjectManager
{
    private :
                            LightHouseTestObjectManager2 ();

        virtual LightPulse *createLightPulseInstance     (const string &lightPulseName);

    protected :
    public :
        virtual                             ~LightHouseTestObjectManager2 ();

        static string                        getServiceName               ();
        static LightHouseTestObjectManager2 *getInstance                  ();
        static WaveServiceId                 getWaveServiceId             ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // LIGHTHOUSETESTOBJECTMANAGER2_H
