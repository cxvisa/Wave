/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#include "Framework/Shutdown/PrismSecondaryNodeConfigureShutdownAgent.h"

namespace WaveNs
{

PrismSecondaryNodeConfigureShutdownAgent::PrismSecondaryNodeConfigureShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismShutdownAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

PrismSecondaryNodeConfigureShutdownAgent::~PrismSecondaryNodeConfigureShutdownAgent ()
{
}

}

