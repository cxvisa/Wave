/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONGLOBALCLEANUPAGENTCONTEXT_H
#define MULTIPARTITIONGLOBALCLEANUPAGENTCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class MultiPartitionGlobalCleanupAgentContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        MultiPartitionGlobalCleanupAgentContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~MultiPartitionGlobalCleanupAgentContext ();

                vector<WaveServiceId> &getEnabledServices                      ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // MULTIPARTITIONGLOBALCLEANUPAGENTCONTEXT_H
