/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Test/NetworkModelTestContext.h"


using namespace WaveNs;

namespace IsleNs
{
NetworkModelTestContext::NetworkModelTestContext (RegressionTestMessage *pRegressionTestMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pRegressionTestMessage, pWaveElement, pSteps, numberOfSteps)
{
}

NetworkModelTestContext::NetworkModelTestContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps)
{
}

NetworkModelTestContext::~NetworkModelTestContext ()
{
}

}
