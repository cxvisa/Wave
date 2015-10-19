/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/WavePrimaryUncontrolledFailoverAgent.h"

namespace WaveNs
{

WavePrimaryUncontrolledFailoverAgent::WavePrimaryUncontrolledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveFailoverAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

WavePrimaryUncontrolledFailoverAgent::~WavePrimaryUncontrolledFailoverAgent ()
{
}

FrameworkObjectManagerFailoverReason WavePrimaryUncontrolledFailoverAgent::getFailoverReason () const
{
    return (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
}

WaveBootReason WavePrimaryUncontrolledFailoverAgent::getBootReason () const
{
    return (WAVE_BOOT_PRIMARY_UNCONTROLLED_FAILOVER_BOOT);
}


}
