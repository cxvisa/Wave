/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMSHUTDOWNAGENTCONTEXT_H
#define PRISMSHUTDOWNAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class PrismShutdownAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        PrismShutdownAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~PrismShutdownAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // PRISMSHUTDOWNAGENTCONTEXT_H
