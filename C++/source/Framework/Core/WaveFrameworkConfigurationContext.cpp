/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkConfigurationContext.h"

namespace WaveNs
{

WaveFrameworkConfigurationContext::WaveFrameworkConfigurationContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const string &waveFrameworkConfigurationFileName)
    : PrismSynchronousLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_waveFrameworkConfigurationFileName (waveFrameworkConfigurationFileName),
      m_syncToStandby (false)
{
}

WaveFrameworkConfigurationContext::~WaveFrameworkConfigurationContext ()
{
}

string &WaveFrameworkConfigurationContext::getWaveFrameworkConfigurationFileName ()
{
    return (m_waveFrameworkConfigurationFileName);
}

WaveFrameworkConfiguration &WaveFrameworkConfigurationContext::getWaveFrameworkConfigurationObject ()
{
    return (m_waveFrameworkConfigurationObject);
}

bool WaveFrameworkConfigurationContext::getSyncToStandby ()
{
    return (m_syncToStandby);
}

void WaveFrameworkConfigurationContext::setSyncToStandby (const bool &syncToStandby)
{
    m_syncToStandby = syncToStandby;
}

}
