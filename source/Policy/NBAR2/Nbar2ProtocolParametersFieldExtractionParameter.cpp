/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolParametersFieldExtractionParameter.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolParametersFieldExtractionParameter::Nbar2ProtocolParametersFieldExtractionParameter ()
    : Nbar2Element ()
{
    addTextAttribute ("help-string", new AttributeString (&m_helpString));
    addTextAttribute ("id",          new AttributeUI64   (&m_id));
    addTextAttribute ("name",        new AttributeString (&m_name));
}

Nbar2ProtocolParametersFieldExtractionParameter::~Nbar2ProtocolParametersFieldExtractionParameter ()
{
}

}

