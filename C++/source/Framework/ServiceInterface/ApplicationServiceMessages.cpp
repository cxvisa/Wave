/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/ApplicationServiceMessages.h"

namespace WaveNs
{

ApplicationServiceMessage::ApplicationServiceMessage ()
    : WaveMessage (0, APPLICATION_SERVICE_GENERIC_MESSAGE)
{
}

ApplicationServiceMessage::ApplicationServiceMessage (WaveServiceId prismServiceId)
    : WaveMessage (prismServiceId, APPLICATION_SERVICE_GENERIC_MESSAGE)
{
}

ApplicationServiceMessage::~ApplicationServiceMessage ()
{
}

void ApplicationServiceMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();
}

void *ApplicationServiceMessage::getInputBuffer1 (UI32 &bufferLength)
{
    return (findBuffer (APPLICATION_SERVICE_GENERIC_MESSAGE, bufferLength));
}

}
