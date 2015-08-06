/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef FILEREPLAYENDAGENTCONTEXT_H
#define FILEREPLAYENDAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class FileReplayEndAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        FileReplayEndAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~FileReplayEndAgentContext ();

                vector<WaveServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<WaveServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // FileReplayEndAGENTCONTEXT_H
