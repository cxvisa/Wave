/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author :  Anand Subramanian                                           *
 ***************************************************************************/

#include "ManagementInterface/ManagementInterfaceServiceIndependentMessage.h"

namespace WaveNs
{

ManagementInterfaceServiceIndependentMessage::ManagementInterfaceServiceIndependentMessage (const string &serviceName, const UI32 &operationId)
    : ManagementInterfaceMessage (serviceName, operationId),
    WaveServiceIndependentMessageBase ()
{
}

ManagementInterfaceServiceIndependentMessage::~ManagementInterfaceServiceIndependentMessage ()
{
}

void ManagementInterfaceServiceIndependentMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();
}

}


