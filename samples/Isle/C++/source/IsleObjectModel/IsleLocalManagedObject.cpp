/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "IsleObjectModel/IsleLocalManagedObject.h"

namespace IsleNs
{

IsleLocalManagedObject::IsleLocalManagedObject (WaveObjectManager *pWaveObjectManager)
    : WaveElement                (pWaveObjectManager),
      WavePersistableObject      (IsleLocalManagedObject::getClassName (), IsleManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager),
      IsleManagedObject          (pWaveObjectManager),
      WaveLocalManagedObjectBase (this),
      IsleLocalManagedObjectBase (this)
{
}

IsleLocalManagedObject::~IsleLocalManagedObject ()
{
}

void IsleLocalManagedObject::setupAttributesForPersistence ()
{
    IsleManagedObject::setupAttributesForPersistence ();

    IsleLocalManagedObjectBase::setupAttributesForPersistence ();
}

void IsleLocalManagedObject::setupAttributesForCreate ()
{
    IsleManagedObject::setupAttributesForCreate ();

    IsleLocalManagedObjectBase::setupAttributesForCreate ();
}

string IsleLocalManagedObject::getClassName ()
{
    return ("IsleLocalManagedObject");
}

}
