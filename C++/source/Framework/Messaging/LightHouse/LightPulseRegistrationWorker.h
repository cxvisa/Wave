/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEREGISTRATIONWORKER_H
#define LIGHTPULSEREGISTRATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class LightPulseDispatchObjectManager;
class LightPulseRegistrationMessage;

class LightPulseRegistrationWorker : public WaveWorker
{
    private :
        void registerForLightPulseMessageHandler (LightPulseRegistrationMessage *pLightPulseRegistrationMessage);

    protected :
    public :
                 LightPulseRegistrationWorker (LightPulseDispatchObjectManager *LightPulseDispatchObjectManager);
        virtual ~LightPulseRegistrationWorker ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // LIGHTPULSEREGISTRATIONWORKER_H
