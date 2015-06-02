/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S                                                  *
 ***************************************************************************/

#ifndef PRISMZEROIZEAGENTCONTEXT_H
#define PRISMZEROIZEAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class PrismZeroizeAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
            PrismZeroizeAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
            virtual                        ~PrismZeroizeAgentContext ();

            vector<PrismServiceId> &getZeroizableServices        ();

    // Now the data members

    private :
        vector<PrismServiceId> m_zeroizableServices;

    protected :
    public :
};

}

#endif // PRISMZEROIZEAGENTCONTEXT_H
