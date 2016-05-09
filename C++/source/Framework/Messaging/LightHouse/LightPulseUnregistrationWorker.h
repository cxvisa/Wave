/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEUNREGISTRATIONWORKER_H
#define LIGHTPULSEUNREGISTRATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class LightPulseDispatchObjectManager;
class LightPulseRegistrationMessage;

class LightPulseUnregistrationWorker : public WaveWorker
{
    private :
        void unregisterForLightPulseMessageHandler (LightPulseRegistrationMessage *pLightPulseRegistrationMessage);

    protected :
    public :
                 LightPulseUnregistrationWorker (LightPulseDispatchObjectManager *LightPulseDispatchObjectManager);
        virtual ~LightPulseUnregistrationWorker ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // LIGHTPULSEUNREGISTRATIONWORKER_H
