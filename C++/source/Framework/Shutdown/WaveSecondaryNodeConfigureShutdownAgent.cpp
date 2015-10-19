/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#include "Framework/Shutdown/WaveSecondaryNodeConfigureShutdownAgent.h"

namespace WaveNs
{

WaveSecondaryNodeConfigureShutdownAgent::WaveSecondaryNodeConfigureShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveShutdownAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

WaveSecondaryNodeConfigureShutdownAgent::~WaveSecondaryNodeConfigureShutdownAgent ()
{
}

}

