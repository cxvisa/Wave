/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author Amit Agrawal                                                   *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTAGENTCONTEXT_H
#define PRISMPOSTBOOTAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class PrismPostbootAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        PrismPostbootAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~PrismPostbootAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // PRISMPOSTBOOTAGENTCONTEXT_H
