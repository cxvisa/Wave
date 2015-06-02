/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolParametersSubClassificationParameter.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolParametersSubClassificationParameter::Nbar2ProtocolParametersSubClassificationParameter ()
    : Nbar2Element ()
{
    addTextAttribute ("help-string", new AttributeString (&m_helpString));
    addTextAttribute ("name",        new AttributeString (&m_name));
}

Nbar2ProtocolParametersSubClassificationParameter::~Nbar2ProtocolParametersSubClassificationParameter ()
{
}

}

