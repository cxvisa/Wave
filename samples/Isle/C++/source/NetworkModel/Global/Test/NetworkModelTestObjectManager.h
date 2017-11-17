/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMODELTESTOBJECTMANAGER_H
#define NETWORKMODELTESTOBJECTMANAGER_H

#include "Regression/WaveTestObjectManager.h"
#include "Regression/RegressionTestMessage.h"

using namespace WaveNs;

namespace IsleNs
{

class NetworkModelTestContext;

class NetworkModelTestObjectManager : public WaveTestObjectManager
{
    private :
                     NetworkModelTestObjectManager ();

        virtual void testRequestHandler            (RegressionTestMessage *pMessage);

                void sampleStep                    (NetworkModelTestContext *pNetworkModelTestContext);

    protected :
    public :
        virtual ~NetworkModelTestObjectManager ();

        static string                         getServiceName ();
        static NetworkModelTestObjectManager *getInstance    ();

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // NETWORKMODELTESTOBJECTMANAGER_H

