/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef PRISMEXTERNALSTATESYNCHRONIZATIONCONTEXT_H
#define PRISMEXTERNALSTATESYNCHRONIZATIONCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{
class PrismExternalStateSynchronizationAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        PrismExternalStateSynchronizationAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~PrismExternalStateSynchronizationAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // PRISMEXTERNALSTATESYNCHRONIZATIONAGENTCONTEXT_H
