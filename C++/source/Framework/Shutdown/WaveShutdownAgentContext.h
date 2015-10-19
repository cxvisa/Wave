/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESHUTDOWNAGENTCONTEXT_H
#define WAVESHUTDOWNAGENTCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveShutdownAgentContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        WaveShutdownAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~WaveShutdownAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // WAVESHUTDOWNAGENTCONTEXT_H
