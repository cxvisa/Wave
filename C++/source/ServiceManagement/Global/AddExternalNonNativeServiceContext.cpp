/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/AddExternalNonNativeServiceContext.h"

namespace WaveNs
{

AddExternalNonNativeServiceContext::AddExternalNonNativeServiceContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps)
{
}

AddExternalNonNativeServiceContext::~AddExternalNonNativeServiceContext ()
{
}

const vector<string> &AddExternalNonNativeServiceContext::getApplicationNames () const
{
    return (m_applicationNames);
}

void AddExternalNonNativeServiceContext::setApplicationNames (const vector<string> &applicationNames)
{
    m_applicationNames = applicationNames;
}

}
