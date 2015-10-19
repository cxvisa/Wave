/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

WaveAsynchronousContextForBootPhases::WaveAsynchronousContextForBootPhases (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_bootReason             (WAVE_BOOT_FIRST_TIME_BOOT),
      m_rollBackFlag           (false)
{
}

WaveAsynchronousContextForBootPhases::~WaveAsynchronousContextForBootPhases ()
{
}

WaveBootReason WaveAsynchronousContextForBootPhases::getBootReason () const
{
    return (m_bootReason);
}

void WaveAsynchronousContextForBootPhases::setBootReason (const WaveBootReason &bootReason)
{
    m_bootReason = bootReason;
}

bool WaveAsynchronousContextForBootPhases::getRollBackFlag () const
{
    return (m_rollBackFlag);
}

void WaveAsynchronousContextForBootPhases::setRollBackFlag (const bool &rollBackFlag)
{
    m_rollBackFlag = rollBackFlag;
}

}
