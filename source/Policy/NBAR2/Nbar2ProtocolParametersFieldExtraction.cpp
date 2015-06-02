/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolParametersFieldExtraction.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

Nbar2ProtocolParametersFieldExtraction::Nbar2ProtocolParametersFieldExtraction ()
{
}

Nbar2ProtocolParametersFieldExtraction::~Nbar2ProtocolParametersFieldExtraction ()
{
}

Nbar2Element *Nbar2ProtocolParametersFieldExtraction::getNbar2ElementByName  (const string &nbar2ElementName)
{
    if ("parameter" == nbar2ElementName)
    {
        Nbar2ProtocolParametersFieldExtractionParameter *pNbar2ProtocolParametersFieldExtractionParameter = new Nbar2ProtocolParametersFieldExtractionParameter ();

        prismAssert (NULL != pNbar2ProtocolParametersFieldExtractionParameter, __FILE__, __LINE__);

        m_parameter.push_back (pNbar2ProtocolParametersFieldExtractionParameter);

        return (pNbar2ProtocolParametersFieldExtractionParameter);
    }
    else
    {
        return (Nbar2Element::getNbar2ElementByName (nbar2ElementName));
    }
}

}

