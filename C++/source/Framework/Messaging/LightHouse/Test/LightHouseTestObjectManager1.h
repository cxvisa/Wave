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


        static UI32 clientDatagramTest        (UI32 argc, vector<string> argv);
        static UI32 serverDatagramTest        (UI32 argc, vector<string> argv);

        static UI32 secureClientDatagramTest  (UI32 argc, vector<string> argv);
        static UI32 secureServerDatagramTest  (UI32 argc, vector<string> argv);

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
