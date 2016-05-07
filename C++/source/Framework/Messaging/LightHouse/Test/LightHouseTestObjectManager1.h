/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETESTOBJECTMANAGER1_H
#define LIGHTHOUSETESTOBJECTMANAGER1_H

#include "Regression/WaveTestObjectManager.h"

namespace WaveNs
{

class RegressionTestMessage;
class LightHouseTestContext;

class LightHouseTestObjectManager1 : public WaveTestObjectManager
{
    private :
             LightHouseTestObjectManager1     ();

        void testRequestHandler               (RegressionTestMessage *pRegressionTestMessage);

        void broadcastTestLightPulse1TestStep (LightHouseTestContext *pLightHouseTestContext);

    protected :
    public :
        virtual                             ~LightHouseTestObjectManager1 ();

        static string                        getServiceName               ();
        static LightHouseTestObjectManager1 *getInstance                  ();
        static WaveServiceId                 getWaveServiceId             ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // LIGHTHOUSETESTOBJECTMANAGER1_H
