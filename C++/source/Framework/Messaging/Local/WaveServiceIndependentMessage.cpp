/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                
 *   All rights reserved.  
 *   Description: This file implements the service independent message
 *                class.  Service independent messages allow for immediate 
 *                handling of the message across any transport (Client,
 *                HaPeer, InterLocation).
 *   Author : Brian Adaniya 
 *   Date   : 10/18/2012                                           
 ***************************************************************************/

#include "Framework/Messaging/Local/WaveServiceIndependentMessage.h"

namespace WaveNs
{

WaveServiceIndependentMessage::WaveServiceIndependentMessage (WaveServiceId serviceCode, UI32 operationCode)
    : WaveMessage (serviceCode, operationCode),
    WaveServiceIndependentMessageBase ()
{
}

WaveServiceIndependentMessage::~WaveServiceIndependentMessage ()
{
}

void WaveServiceIndependentMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization (); 
}

}
