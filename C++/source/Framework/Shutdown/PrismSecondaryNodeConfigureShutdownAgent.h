/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#ifndef PRISMSECONDARYNODECONFIGURESHUTDOWNAGENT_H
#define PRISMSECONDARYNODECONFIGURESHUTDOWNAGENT_H

#include "Framework/Shutdown/PrismShutdownAgent.h"

namespace WaveNs
{

class PrismSecondaryNodeConfigureShutdownAgent : public PrismShutdownAgent
{
    private :
    protected :
    public :
         PrismSecondaryNodeConfigureShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~PrismSecondaryNodeConfigureShutdownAgent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMSECONDARYNODECONFIGURESHUTDOWNAGENT_H

