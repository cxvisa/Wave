/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/ShardableResourceCategory.h"

namespace WaveNs
{

ShardableResourceCategory::ShardableResourceCategory (WaveObjectManager *pWaveObjectManager)
    : WaveElement                (pWaveObjectManager),
      WavePersistableObject      (ShardableResourceCategory::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager)
{
}

ShardableResourceCategory::~ShardableResourceCategory ()
{
}

string ShardableResourceCategory::getClassName ()
{
    return ("ShardableResourceCategory");
}

void ShardableResourceCategory::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    // This class Specific Attributes below
}

void ShardableResourceCategory::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    // This class Specific Attributes below
}

}
