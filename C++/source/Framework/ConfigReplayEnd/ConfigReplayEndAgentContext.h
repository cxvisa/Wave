/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef CONFIGREPLAYENDAGENTCONTEXT_H
#define CONFIGREPLAYENDAGENTCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class ConfigReplayEndAgentContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        ConfigReplayEndAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~ConfigReplayEndAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // ConfigReplayEndAGENTCONTEXT_H
