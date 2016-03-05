/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "AddExternalNonNativeServiceContext.h"

namespace WaveNs
{

AddExternalNonNativeServiceContext::AddExternalNonNativeServiceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

AddExternalNonNativeServiceContext::~AddExternalNonNativeServiceContext ()
{
}

}
