/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEEXTERNALSTATESYNCHRONIZATIONCONTEXT_H
#define WAVEEXTERNALSTATESYNCHRONIZATIONCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{
class WaveExternalStateSynchronizationAgentContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        WaveExternalStateSynchronizationAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~WaveExternalStateSynchronizationAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // WAVEEXTERNALSTATESYNCHRONIZATIONAGENTCONTEXT_H
