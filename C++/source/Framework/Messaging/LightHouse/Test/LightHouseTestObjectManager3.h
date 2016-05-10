/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETESTOBJECTMANAGER3_H
#define LIGHTHOUSETESTOBJECTMANAGER3_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class RegressionTestMessage;
class WaveAsynchronousContextForBootPhases;
class LightHouseTestLightPulse1;

class LightHouseTestObjectManager3 : public WaveLocalObjectManager
{
    private :
                     LightHouseTestObjectManager3     ();

        virtual void listenForEvents                  (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

                void lightHouseTestLightPulse1Handler (const LightHouseTestLightPulse1 *&pLightHouseTestLightPulse1);

    protected :
    public :
        virtual                             ~LightHouseTestObjectManager3 ();

        static string                        getServiceName               ();
        static LightHouseTestObjectManager3 *getInstance                  ();
        static WaveServiceId                 getWaveServiceId             ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // LIGHTHOUSETESTOBJECTMANAGER3_H
