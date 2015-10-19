/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S                                                  *
 ***************************************************************************/

#ifndef WAVEZEROIZEAGENTCONTEXT_H
#define WAVEZEROIZEAGENTCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveZeroizeAgentContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
            WaveZeroizeAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
            virtual                        ~WaveZeroizeAgentContext ();

            vector<WaveServiceId> &getZeroizableServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_zeroizableServices;

    protected :
    public :
};

}

#endif // WAVEZEROIZEAGENTCONTEXT_H
