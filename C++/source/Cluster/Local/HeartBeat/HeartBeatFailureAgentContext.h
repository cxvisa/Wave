/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HEARTBEATFAILUREAGENTCONTEXT_H
#define HEARTBEATFAILUREAGENTCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class HeartBeatFailureAgentContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        HeartBeatFailureAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~HeartBeatFailureAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // HEARTBEATFAILUREAGENTCONTEXT_H
