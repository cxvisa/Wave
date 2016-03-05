/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "ServiceManagement/Global/ShardData.h"

namespace WaveNs
{

ShardData::ShardData (WaveObjectManager *pWaveObjectManager)
    : WaveElement                (pWaveObjectManager),
      WavePersistableObject      (ShardData::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager)
{
}

ShardData::~ShardData ()
{
}

string ShardData::getClassName ()
{
    return ("ShardData");
}

void ShardData::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    // This class Specific Attributes below
}

void ShardData::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    // This class Specific Attributes below
}

}
