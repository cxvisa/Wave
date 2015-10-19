/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveDebugInformationContext.h"

namespace WaveNs
{

WaveDebugInformationContext::WaveDebugInformationContext (WaveMessage* pWaveMessage, WaveElement* pWaveElement, WaveLinearSequencerStep* pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
    m_debugInformation  ("")
{
}

WaveDebugInformationContext::~WaveDebugInformationContext ()
{
}

void WaveDebugInformationContext::setDebugInformation (const string &debugInformation)
{
    m_debugInformation = debugInformation;
}

void WaveDebugInformationContext::appendDebugInformation (const string &debugInformation)
{
    if ("" != debugInformation)
    {
        m_debugInformation += debugInformation;
    }
}

const string & WaveDebugInformationContext::getDebugInformation () const
{
    return (m_debugInformation);
}

}

