/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/Zeroize/ZeroizeForFIPSLinearSequencerContext.h"


namespace WaveNs
{
	
    ZeroizeForFIPSLinearSequencerContext::ZeroizeForFIPSLinearSequencerContext 
    (
        WaveMessage                *pWaveMessage, 
        WaveElement                *pWaveElement, 
        PrismLinearSequencerStep    *pSteps, 
        UI32                        numberOfSteps

    ): WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
    {
    }

    ZeroizeForFIPSLinearSequencerContext::~ZeroizeForFIPSLinearSequencerContext()
    {
    }


}
