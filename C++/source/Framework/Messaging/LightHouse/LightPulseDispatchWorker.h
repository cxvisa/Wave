/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEDISPATCHWORKER_H
#define LIGHTPULSEDISPATCHWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class LightPulseDispatchObjectManager;
class LightPulseDispatchMessage;

class LightPulseDispatchWorker : public WaveWorker
{
    private :
        void dispatchReceivedLightPulseMessageHandler (LightPulseDispatchMessage *pLightPulseDispatchMessage);

    protected :
    public :
                 LightPulseDispatchWorker (LightPulseDispatchObjectManager *LightPulseDispatchObjectManager);
        virtual ~LightPulseDispatchWorker ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // LIGHTPULSEDISPATCHWORKER_H
