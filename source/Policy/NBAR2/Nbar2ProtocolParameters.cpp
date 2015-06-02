/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/


#include "Policy/NBAR2/Nbar2ProtocolParameters.h"

namespace WaveNs
{

Nbar2ProtocolParameters::Nbar2ProtocolParameters ()
    : Nbar2Element ()
{
    addNbar2Element ("sub-classification", &m_subClassification);
    addNbar2Element ("field-extraction",   &m_filedExtraction);
}

Nbar2ProtocolParameters::~Nbar2ProtocolParameters ()
{
}

}

