/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDNODESTOCLUSTERCONTEXT_H
#define ADDNODESTOCLUSTERCONTEXT_H

#include "Framework/Core/CreateClusterWithNodesContext.h"

namespace WaveNs
{

class AddNodesToClusterContext : public CreateClusterWithNodesContext
{
    private :
    protected :
    public :
                 AddNodesToClusterContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~AddNodesToClusterContext ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif// ADDNODESTOCLUSTERCONTEXT_H
