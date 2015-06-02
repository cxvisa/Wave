/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 **************************************************************************/

#include "ManagementInterface/ClientInterface/UnifiedClientDeleteMessage.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ClientInterface/UnifiedClientCommon.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

UnifiedClientDeleteMessage::UnifiedClientDeleteMessage ()
    : UnifiedClientUpdateMessage (UNIFIEDCLIENTDELETE)
{
}

UnifiedClientDeleteMessage::UnifiedClientDeleteMessage (const WaveManagedObjectAsynchronousPluginContext *pWaveManagedObjectAsynchronousPluginContext)
   : UnifiedClientUpdateMessage (UNIFIEDCLIENTDELETE, pWaveManagedObjectAsynchronousPluginContext)
{
}

UnifiedClientDeleteMessage::~UnifiedClientDeleteMessage ()
{
}

void UnifiedClientDeleteMessage::setupAttributesForSerialization()
{
    UnifiedClientUpdateMessage::setupAttributesForSerialization ();
}

const void *UnifiedClientDeleteMessage::getCStructureForInputs ()
{
    UnifiedClientMessage_t *pInput                  = (UnifiedClientMessage_t *) (UnifiedClientUpdateMessage::getCStructureForInputs ()); 

    return (pInput);
}

void UnifiedClientDeleteMessage::loadOutputsFromCStructure (const void *pOutputCStructure)
{
    UnifiedClientUpdateMessage::loadOutputsFromCStructure (pOutputCStructure);
}


}
