/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEDISPATCHOBJECTMANAGER_H
#define LIGHTPULSEDISPATCHOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class LightPulseDispatchWorker;
class LightPulseRegistrationWorker;
class LightPulseUnregistrationWorker;

class LightPulseDispatchObjectManager : public WaveLocalObjectManager
{
    private :
        LightPulseDispatchObjectManager ();

    protected :
    public :
        virtual                                ~LightPulseDispatchObjectManager ();

        static string                           getServiceName                  ();
        static LightPulseDispatchObjectManager *getInstance                     ();
        static WaveServiceId                    getWaveServiceId                ();

        // Now the data members

    private :
        LightPulseDispatchWorker       *m_pLightPulseDispatchWorker;
        LightPulseRegistrationWorker   *m_pLightPulseRegistrationWorker;
        LightPulseUnregistrationWorker *m_pLightPulseUnregistrationWorker;

    protected :
    public :
};

}

#endif // LIGHTPULSEDISPATCHOBJECTMANAGER_H
