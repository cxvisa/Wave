/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "IsleObjectModel/IsleLocalManagedObjectBase.h"
#include "IsleObjectModel/IsleManagedObject.h"

using namespace WaveNs;

namespace IsleNs
{

IsleLocalManagedObjectBase::IsleLocalManagedObjectBase (IsleManagedObject *pIsleManagedObject)
    : WaveLocalManagedObjectBase (dynamic_cast<WaveManagedObject *> (pIsleManagedObject))
{
}

IsleLocalManagedObjectBase::~IsleLocalManagedObjectBase ()
{
}

string IsleLocalManagedObjectBase::getClassName ()
{
    return ("IsleLocalManagedObjectBase");
}

void IsleLocalManagedObjectBase::setupAttributesForPersistence ()
{
    WaveLocalManagedObjectBase::setupAttributesForPersistence ();
}

void IsleLocalManagedObjectBase::setupAttributesForCreate ()
{
    WaveLocalManagedObjectBase::setupAttributesForCreate ();
}


}
