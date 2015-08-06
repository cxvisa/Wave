/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/WaveManagedObjectMessage.h"

namespace WaveNs
{

WaveManagedObjectMessage::WaveManagedObjectMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode)
{
}

WaveManagedObjectMessage::WaveManagedObjectMessage (WaveServiceId serviceCode, UI32 operationCode, const ObjectId &waveManagedObjectId)
    : WaveMessage          (serviceCode, operationCode),
      m_waveManagedObjectId (waveManagedObjectId)
{
}

WaveManagedObjectMessage::~WaveManagedObjectMessage ()
{
}

void WaveManagedObjectMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeObjectId (&m_waveManagedObjectId, "waveManagedObjectId"));
}

}
