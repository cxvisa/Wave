/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#ifndef WAVESECONDARYNODEREJOINSHUTDOWNAGENT_H
#define WAVESECONDARYNODEREJOINSHUTDOWNAGENT_H

#include "Framework/Shutdown/WaveShutdownAgent.h"

namespace WaveNs
{

class WaveSecondaryNodeRejoinShutdownAgent : public WaveShutdownAgent
{
    private :
    protected :
    public :
         WaveSecondaryNodeRejoinShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~WaveSecondaryNodeRejoinShutdownAgent ();
         virtual ResourceId execute ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESECONDARYNODEREJOINSHUTDOWNAGENT_H

