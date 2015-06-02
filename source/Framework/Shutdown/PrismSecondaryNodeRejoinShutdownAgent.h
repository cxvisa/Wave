/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#ifndef PRISMSECONDARYNODEREJOINSHUTDOWNAGENT_H
#define PRISMSECONDARYNODEREJOINSHUTDOWNAGENT_H

#include "Framework/Shutdown/PrismShutdownAgent.h"

namespace WaveNs
{

class PrismSecondaryNodeRejoinShutdownAgent : public PrismShutdownAgent
{
    private :
    protected :
    public :
         PrismSecondaryNodeRejoinShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~PrismSecondaryNodeRejoinShutdownAgent ();
         virtual ResourceId execute ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMSECONDARYNODEREJOINSHUTDOWNAGENT_H

