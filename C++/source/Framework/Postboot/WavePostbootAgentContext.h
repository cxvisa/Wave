/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Amit Agrawal                                                   *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTAGENTCONTEXT_H
#define WAVEPOSTBOOTAGENTCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class WavePostbootAgentContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        WavePostbootAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~WavePostbootAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // WAVEPOSTBOOTAGENTCONTEXT_H
