/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETRANSPORTOBJECTMANAGER_H
#define LIGHTHOUSETRANSPORTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class LightHouseTransportBroadcastLightPulseWorker;

class LightHouseTransportObjectManager : public WaveLocalObjectManager
{
    private :
        LightHouseTransportObjectManager ();

    protected :
    public :

        virtual                                  ~LightHouseTransportObjectManager ();

        static  string                            getServiceName                   ();
        static  LightHouseTransportObjectManager *getInstance                      ();
        static  WaveServiceId                     getWaveServiceId                 ();

        // Now the data members

    private :
        LightHouseTransportBroadcastLightPulseWorker *m_pLightHouseTransportBroadcastLightPulseWorker;

    protected :
    public :
};

}

#endif // LIGHTHOUSETRANSPORTOBJECTMANAGER_H
