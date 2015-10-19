/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil ChannaveeraSetty                                        *
 ***************************************************************************/

#ifndef SECONDARYNODECLUSTERPHASE3CONTEXT_H
#define SECONDARYNODECLUSTERPHASE3CONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/Core/SecondaryNodeClusterContext.h"

namespace WaveNs
{

class SecondaryNodeClusterPhase3Context: public SecondaryNodeClusterContext 
{
    private :
    protected :
    public :
                 SecondaryNodeClusterPhase3Context (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag = true, bool clusterHaSyncInProgressFlag = false);
                 SecondaryNodeClusterPhase3Context (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag = true, bool clusterHaSyncInProgressFlag = false);
        virtual ~SecondaryNodeClusterPhase3Context ();

    // Now the data members

    private :
        bool    m_resetSecondaryNodeClusterCreationFlag;

    protected :
    public :
};

}

#endif // SECONDARYNODECLUSTERPHASE3CONTEXT_H
