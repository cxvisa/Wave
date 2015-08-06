/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForShutdownPhases.h"

namespace WaveNs
{

WaveAsynchronousContextForShutDownPhases::WaveAsynchronousContextForShutDownPhases (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_shutDownReason         (WAVE_SHUTDOWN_FIRST_TIME)
{
}

WaveAsynchronousContextForShutDownPhases::~WaveAsynchronousContextForShutDownPhases ()
{
}

WaveShutDownReason WaveAsynchronousContextForShutDownPhases::getShutDownReason () const
{
    return (m_shutDownReason);
}

void WaveAsynchronousContextForShutDownPhases::setShutDownReason (const WaveShutDownReason &shutDownReason)
{
    m_shutDownReason = shutDownReason;
}

}
