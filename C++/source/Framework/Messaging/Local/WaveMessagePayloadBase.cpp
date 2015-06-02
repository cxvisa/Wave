/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/Local/WaveMessagePayloadBase.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveMessagePayloadBase::WaveMessagePayloadBase (PrismMessage *pPrismMessage)
    : m_pPrismMessage (pPrismMessage)
{
    prismAssert (NULL != m_pPrismMessage, __FILE__, __LINE__);
}

WaveMessagePayloadBase::~WaveMessagePayloadBase ()
{
}

void WaveMessagePayloadBase::addSerializableAttribute (Attribute *pAttribute)
{
    m_pPrismMessage->addSerializableAttribute (pAttribute);
}

}
