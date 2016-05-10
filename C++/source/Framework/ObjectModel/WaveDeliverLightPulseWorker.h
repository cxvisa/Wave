/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEDELIVERLIGHTPULSEWORKER_H
#define WAVEDELIVERLIGHTPULSEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveDeliverLightPulseMessage;

class WaveDeliverLightPulseWorker : public WaveWorker
{
    private :
        void deliverLightPulseHandler (WaveDeliverLightPulseMessage *pWaveDeliverLightPulseMessage);

    protected :
    public :
         WaveDeliverLightPulseWorker (WaveObjectManager *pWaveObjectManager);
        ~WaveDeliverLightPulseWorker ();

        // Now the data member

    private :
    protected :
    public :
};

}

#endif // WAVEDELIVERLIGHTPULSEWORKER_H
