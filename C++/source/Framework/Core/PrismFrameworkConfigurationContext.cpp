/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/PrismFrameworkConfigurationContext.h"

namespace WaveNs
{

PrismFrameworkConfigurationContext::PrismFrameworkConfigurationContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const string &prismFrameworkConfigurationFileName)
    : PrismSynchronousLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_prismFrameworkConfigurationFileName (prismFrameworkConfigurationFileName),
      m_syncToStandby (false)
{
}

PrismFrameworkConfigurationContext::~PrismFrameworkConfigurationContext ()
{
}

string &PrismFrameworkConfigurationContext::getPrismFrameworkConfigurationFileName ()
{
    return (m_prismFrameworkConfigurationFileName);
}

PrismFrameworkConfiguration &PrismFrameworkConfigurationContext::getPrismFrameworkConfigurationObject ()
{
    return (m_prismFrameworkConfigurationObject);
}

bool PrismFrameworkConfigurationContext::getSyncToStandby ()
{
    return (m_syncToStandby);
}

void PrismFrameworkConfigurationContext::setSyncToStandby (const bool &syncToStandby)
{
    m_syncToStandby = syncToStandby;
}

}
