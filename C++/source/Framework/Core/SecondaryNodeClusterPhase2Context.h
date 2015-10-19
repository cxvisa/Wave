/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef SECONDARYNODECLUSTERPHASE2CONTEXT_H
#define SECONDARYNODECLUSTERPHASE2CONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/Core/SecondaryNodeClusterContext.h"

namespace WaveNs
{

class SecondaryNodeClusterPhase2Context: public SecondaryNodeClusterContext 
{
    private :
    protected :
    public :
                 SecondaryNodeClusterPhase2Context (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag = true);
                 SecondaryNodeClusterPhase2Context (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, bool resetSecondaryNodeClusterCreationFlag = true);
        virtual ~SecondaryNodeClusterPhase2Context ();

    // Now the data members

    private :
        bool    m_resetSecondaryNodeClusterCreationFlag;
    protected :
    public :
};

}

#endif // SECONDARYNODECLUSTERPHASE2CONTEXT_H
