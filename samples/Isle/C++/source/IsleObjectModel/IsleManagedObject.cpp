/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "IsleObjectModel/IsleManagedObject.h"
#include "WaveResourceIdEnums.h"

namespace IsleNs
{

IsleManagedObject::IsleManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement           (pWaveObjectManager),
      WavePersistableObject (IsleManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject     (pWaveObjectManager)
{
    //setEmptyNeededOnPersistentBoot (true);
    //setEmptyNeededOnPersistentBootWithDefault (true);

    setGenericStatus  (WAVE_MANAGED_OBJECT_GENERIC_STATUS_GOOD);
    setSpecificStatus (WAVE_MANAGED_OBJECT_GENERIC_STATUS_GOOD);
}

IsleManagedObject::~IsleManagedObject ()
{
}

string IsleManagedObject::getClassName ()
{
    return ("IsleManagedObject");
}

void IsleManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();
}

void IsleManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();
}

}
