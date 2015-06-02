/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef SLOTFAILOVERAGENTCONTEXT_H
#define SLOTFAILOVERAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class SlotFailoverAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        SlotFailoverAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~SlotFailoverAgentContext ();

                vector<PrismServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<PrismServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // SLOTFAILOVERAGENTCONTEXT_H
