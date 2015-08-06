/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/HaBootCompleteForThisLocationEvent.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

HaBootCompleteForThisLocationEvent::HaBootCompleteForThisLocationEvent ()
    : PrismEvent (PrismFrameworkObjectManager::getWaveServiceId (), HA_BOOT_COMPLETE_FOR_THIS_LOCATION)
{
}

HaBootCompleteForThisLocationEvent::~HaBootCompleteForThisLocationEvent ()
{
}

void HaBootCompleteForThisLocationEvent::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();
}

}
