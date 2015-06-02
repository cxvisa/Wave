/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/PrismPrimaryControlledFailoverAgent.h"

namespace WaveNs
{

PrismPrimaryControlledFailoverAgent::PrismPrimaryControlledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismFailoverAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

PrismPrimaryControlledFailoverAgent::~PrismPrimaryControlledFailoverAgent ()
{
}

FrameworkObjectManagerFailoverReason PrismPrimaryControlledFailoverAgent::getFailoverReason () const
{
    return (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED);
}

WaveBootReason PrismPrimaryControlledFailoverAgent::getBootReason () const
{
    return (WAVE_BOOT_PRIMARY_CONTROLLED_FAILOVER_BOOT);
}

}
