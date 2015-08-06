/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/WaveManagedObjectMessage.h"

namespace WaveNs
{

WaveManagedObjectMessage::WaveManagedObjectMessage (WaveServiceId serviceCode, UI32 operationCode)
    : PrismMessage (serviceCode, operationCode)
{
}

WaveManagedObjectMessage::WaveManagedObjectMessage (WaveServiceId serviceCode, UI32 operationCode, const ObjectId &waveManagedObjectId)
    : PrismMessage          (serviceCode, operationCode),
      m_waveManagedObjectId (waveManagedObjectId)
{
}

WaveManagedObjectMessage::~WaveManagedObjectMessage ()
{
}

void WaveManagedObjectMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeObjectId (&m_waveManagedObjectId, "waveManagedObjectId"));
}

}
