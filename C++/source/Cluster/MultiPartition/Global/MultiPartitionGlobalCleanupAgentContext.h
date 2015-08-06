/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONGLOBALCLEANUPAGENTCONTEXT_H
#define MULTIPARTITIONGLOBALCLEANUPAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class MultiPartitionGlobalCleanupAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        MultiPartitionGlobalCleanupAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
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
