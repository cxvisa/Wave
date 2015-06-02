/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef CONFIGREPLAYENDAGENTCONTEXT_H
#define CONFIGREPLAYENDAGENTCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include <vector>

using namespace std;

namespace WaveNs
{

class ConfigReplayEndAgentContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                        ConfigReplayEndAgentContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                        ~ConfigReplayEndAgentContext ();

                vector<PrismServiceId> &getEnabledServices        ();

    // Now the data members

    private :
        vector<PrismServiceId> m_enabledServices;

    protected :
    public :
};

}

#endif // ConfigReplayEndAGENTCONTEXT_H
