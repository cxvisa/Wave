/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/
#include "ManagementInterface/ClientInterface/UnifiedClientNotifyMessage.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ClientInterface/UnifiedClientCommon.h"
#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeResourceId.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{
	 
UnifiedClientNotifyMessage::UnifiedClientNotifyMessage ()
    : ManagementInterfaceMessage (WaveUserInterfaceObjectManager::getWaveServiceName (), UNIFIEDCLIENTNOTIFY)
{
}

UnifiedClientNotifyMessage::~UnifiedClientNotifyMessage ()
{
}
 
void UnifiedClientNotifyMessage::setupAttributesForSerialization()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
	     
    addSerializableAttribute (new AttributeUI32 (&m_backendNotifyValue, "backendNotifyValue"));
}

void UnifiedClientNotifyMessage::setbackendNotifyValue(UI32 &backendNotifyValue)
{
    m_backendNotifyValue =backendNotifyValue;
}
 
UI32 UnifiedClientNotifyMessage::getbackendNotifyValue()  
{
    return (m_backendNotifyValue);
}

const void *UnifiedClientNotifyMessage::getCStructureForInputs ()
{
    UnifiedClientNotifyMessage_t *pInput                  = new UnifiedClientNotifyMessage_t ();

    waveAssert (NULL != pInput, __FILE__, __LINE__);

    pInput->backendNotifyValue = m_backendNotifyValue;

    return (pInput);
}

void UnifiedClientNotifyMessage::deleteCStructureForInputs (const void *pInputStruct)
{
    return;
}

}
