/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/WavePrimaryControlledFailoverAgent.h"

namespace WaveNs
{

WavePrimaryControlledFailoverAgent::WavePrimaryControlledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveFailoverAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

WavePrimaryControlledFailoverAgent::~WavePrimaryControlledFailoverAgent ()
{
}

FrameworkObjectManagerFailoverReason WavePrimaryControlledFailoverAgent::getFailoverReason () const
{
    return (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);
}

WaveBootReason WavePrimaryControlledFailoverAgent::getBootReason () const
{
    return (WAVE_BOOT_PRIMARY_CONTROLLED_FAILOVER_BOOT);
}

}
