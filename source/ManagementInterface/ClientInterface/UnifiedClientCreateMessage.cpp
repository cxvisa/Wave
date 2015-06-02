/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 **************************************************************************/

#include "ManagementInterface/ClientInterface/UnifiedClientCreateMessage.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ClientInterface/UnifiedClientCommon.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

UnifiedClientCreateMessage::UnifiedClientCreateMessage ()
    : UnifiedClientUpdateMessage (UNIFIEDCLIENTCREATE)
{
}

UnifiedClientCreateMessage::UnifiedClientCreateMessage (const WaveManagedObjectAsynchronousPluginContext *pWaveManagedObjectAsynchronousPluginContext)
   : UnifiedClientUpdateMessage (UNIFIEDCLIENTCREATE, pWaveManagedObjectAsynchronousPluginContext)
{
}

UnifiedClientCreateMessage::~UnifiedClientCreateMessage ()
{
}

void UnifiedClientCreateMessage::setupAttributesForSerialization()
{
    UnifiedClientUpdateMessage::setupAttributesForSerialization ();
}

const void *UnifiedClientCreateMessage::getCStructureForInputs ()
{
    UnifiedClientMessage_t *pInput                  = (UnifiedClientMessage_t *) (UnifiedClientUpdateMessage::getCStructureForInputs ()); 

    return (pInput);
}

void UnifiedClientCreateMessage::loadOutputsFromCStructure (const void *pOutputCStructure)
{
    UnifiedClientUpdateMessage::loadOutputsFromCStructure (pOutputCStructure);
}


}
