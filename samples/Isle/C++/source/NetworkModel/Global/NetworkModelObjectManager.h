/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMODELOBJECTMANAGER_H
#define NETWORKMODELOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

#include <string>

using namespace WaveNs;
using namespace std;

namespace IsleNs
{

class HypervisorWorker;
class BridgeWorker;
class InterfaceWorker;

class NetworkModelObjectManager : public WaveObjectManager
{
    private :
        NetworkModelObjectManager ();

    protected :
    public :
        virtual                           ~NetworkModelObjectManager ();

        static  string                     getServiceName            ();
        static  NetworkModelObjectManager *getInstance               ();

        // Now the data members

    private :
        HypervisorWorker *m_pHypervisorWorker;
        BridgeWorker     *m_pBridgeWorker;
        InterfaceWorker  *m_pInterfaceWorker;

    protected :
    public :
};

}

#endif // NETWORKMODELOBJECTMANAGER_H
