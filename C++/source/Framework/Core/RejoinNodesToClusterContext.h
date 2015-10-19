/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REJOINNODESTOCLUSTERCONTEXT_H
#define REJOINNODESTOCLUSTERCONTEXT_H

#include "Framework/Core/DeleteNodesFromClusterContext.h"

namespace WaveNs
{

class RejoinNodesToClusterContext : public DeleteNodesFromClusterContext
{
    private :
    protected :
    public :
                 RejoinNodesToClusterContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~RejoinNodesToClusterContext ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // REJOINNODESTOCLUSTERCONTEXT_H
