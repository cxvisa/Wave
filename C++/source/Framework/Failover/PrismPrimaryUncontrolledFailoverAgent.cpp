/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Failover/PrismPrimaryUncontrolledFailoverAgent.h"

namespace WaveNs
{

PrismPrimaryUncontrolledFailoverAgent::PrismPrimaryUncontrolledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : PrismFailoverAgent (pWaveObjectManager, currentFrameworkSequenceGenerator)
{
}

PrismPrimaryUncontrolledFailoverAgent::~PrismPrimaryUncontrolledFailoverAgent ()
{
}

FrameworkObjectManagerFailoverReason PrismPrimaryUncontrolledFailoverAgent::getFailoverReason () const
{
    return (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
}

WaveBootReason PrismPrimaryUncontrolledFailoverAgent::getBootReason () const
{
    return (WAVE_BOOT_PRIMARY_UNCONTROLLED_FAILOVER_BOOT);
}


}
