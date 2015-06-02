/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONCLEANUPAGENTCONTEXT_H
#define MULTIPARTITIONCLEANUPAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class MultiPartitionCleanupAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        MultiPartitionCleanupAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~MultiPartitionCleanupAgentContext ();

                vector<PrismServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<PrismServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // MULTIPARTITIONCLEANUPAGENTCONTEXT_H
