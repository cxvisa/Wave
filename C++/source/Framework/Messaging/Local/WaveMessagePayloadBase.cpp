/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/WaveMessagePayloadBase.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveMessagePayloadBase::WaveMessagePayloadBase (WaveMessage *pWaveMessage)
    : m_pWaveMessage (pWaveMessage)
{
    waveAssert (NULL != m_pWaveMessage, __FILE__, __LINE__);
}

WaveMessagePayloadBase::~WaveMessagePayloadBase ()
{
}

void WaveMessagePayloadBase::addSerializableAttribute (Attribute *pAttribute)
{
    m_pWaveMessage->addSerializableAttribute (pAttribute);
}

}
