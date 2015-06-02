/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil C                                                       *
 **************************************************************************/

#include "ManagementInterface/ClientInterface/UnifiedClientPostbootMessage.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "ManagementInterface/ClientInterface/UnifiedClientCommon.h"
#include "Framework/Attributes/AttributeStringVectorVector.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

UnifiedClientPostbootMessage::UnifiedClientPostbootMessage ()
    : UnifiedClientUpdateMessage (UNIFIEDCLIENTPOSTBOOT)
{
}

UnifiedClientPostbootMessage::UnifiedClientPostbootMessage (const GetHardwareConfigurationDetailsForPostbootContext *pContext)
   : UnifiedClientUpdateMessage (UNIFIEDCLIENTPOSTBOOT, pContext)
{
}

UnifiedClientPostbootMessage::~UnifiedClientPostbootMessage ()
{
}

void UnifiedClientPostbootMessage::setupAttributesForSerialization()
{   
    UnifiedClientUpdateMessage::setupAttributesForSerialization ();
}

void UnifiedClientPostbootMessage::initializeFromContext( const WaveManagedObjectAsynchronousPluginContext *pContext )
{
    UnifiedClientUpdateMessage::initializeFromContext( pContext );
}

const void *UnifiedClientPostbootMessage::getCStructureForInputs ()
{  
    UnifiedClientMessage_t *pInput                  = (UnifiedClientMessage_t *) (UnifiedClientUpdateMessage::getCStructureForInputs ()); 
    return (pInput);
}

void UnifiedClientPostbootMessage::loadOutputsFromCStructure (const void *pOutputCStructure)
{
}

}
