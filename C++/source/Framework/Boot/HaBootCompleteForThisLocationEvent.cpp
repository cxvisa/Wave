/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/HaBootCompleteForThisLocationEvent.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"

namespace WaveNs
{

HaBootCompleteForThisLocationEvent::HaBootCompleteForThisLocationEvent ()
    : WaveEvent (WaveFrameworkObjectManager::getWaveServiceId (), HA_BOOT_COMPLETE_FOR_THIS_LOCATION)
{
}

HaBootCompleteForThisLocationEvent::~HaBootCompleteForThisLocationEvent ()
{
}

void HaBootCompleteForThisLocationEvent::setupAttributesForSerialization ()
{
    WaveEvent::setupAttributesForSerialization ();
}

}
