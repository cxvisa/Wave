/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#ifndef WAVESECONDARYNODECONFIGURESHUTDOWNAGENT_H
#define WAVESECONDARYNODECONFIGURESHUTDOWNAGENT_H

#include "Framework/Shutdown/WaveShutdownAgent.h"

namespace WaveNs
{

class WaveSecondaryNodeConfigureShutdownAgent : public WaveShutdownAgent
{
    private :
    protected :
    public :
         WaveSecondaryNodeConfigureShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~WaveSecondaryNodeConfigureShutdownAgent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESECONDARYNODECONFIGURESHUTDOWNAGENT_H

