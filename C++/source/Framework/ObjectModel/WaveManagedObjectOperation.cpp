/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectOperation.h"

namespace WaveNs
{

WaveManagedObjectOperation::WaveManagedObjectOperation ()
{
}

WaveManagedObjectOperation::~WaveManagedObjectOperation ()
{
}

void WaveManagedObjectOperation::setReason (const ResourceId &reason)
{
    m_reason = reason;
}

ResourceId WaveManagedObjectOperation::getReason () const
{
    return (m_reason);
}

}
