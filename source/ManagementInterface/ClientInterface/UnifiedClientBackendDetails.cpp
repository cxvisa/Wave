/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/

#include "Framework/Attributes/Attribute.h"
#include "Framework/Attributes/AttributeResourceId.h"
#include "UnifiedClientBackendDetails.h"

namespace WaveNs
{
    
UnifiedClientBackendDetails::UnifiedClientBackendDetails ()
{
}

UnifiedClientBackendDetails::~UnifiedClientBackendDetails ()
{
}

void UnifiedClientBackendDetails::setClientName (string &clientName)
{
    m_clientName = clientName;    
}

string UnifiedClientBackendDetails::getClientName ()
{
    return (m_clientName);    
}

void UnifiedClientBackendDetails::setBackendNotifyValue (UI32 &backendNotifyValue)
{
    m_backendNotifyValue = backendNotifyValue;        
}

UI32 UnifiedClientBackendDetails::getBackendNotifyValue ()
{
    return (m_backendNotifyValue);    
}


}
