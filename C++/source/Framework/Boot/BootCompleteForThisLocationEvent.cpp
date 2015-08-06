/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/BootCompleteForThisLocationEvent.h"
#include "Framework/Boot/BootTypes.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

BootCompleteForThisLocationEvent::BootCompleteForThisLocationEvent (bool flagSchemaChange)
    : WaveEvent (PrismFrameworkObjectManager::getWaveServiceId (), BOOT_COMPLETE_FOR_THIS_LOCATION),
      m_logSchemaChangeFlag (flagSchemaChange)
{
}

BootCompleteForThisLocationEvent::~BootCompleteForThisLocationEvent ()
{
}

void BootCompleteForThisLocationEvent::setupAttributesForSerialization ()
{
    WaveEvent::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeBool (&m_logSchemaChangeFlag, "logSchemaChangeFlag"));
}

bool BootCompleteForThisLocationEvent::needLogAfterSchemaChange () const
{
    return (m_logSchemaChangeFlag);
}

}
