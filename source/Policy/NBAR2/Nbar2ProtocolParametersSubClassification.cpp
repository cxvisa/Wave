/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolParametersSubClassification.h"
#include "Framework/Types/Types.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

Nbar2ProtocolParametersSubClassification::Nbar2ProtocolParametersSubClassification ()
    : Nbar2Element ()
{
}

Nbar2ProtocolParametersSubClassification::~Nbar2ProtocolParametersSubClassification ()
{
    UI32 numberOfContents = m_content.size ();
    UI32 i                = 0;

    for (i = 0; i < numberOfContents; i++)
    {
        delete (m_content[i]);
    }
}

Nbar2Element *Nbar2ProtocolParametersSubClassification::getNbar2ElementByName (const string &nbar2ElementName)
{
    if ("parameter" == nbar2ElementName)
    {
        Nbar2ProtocolParametersSubClassificationParameter *pNbar2ProtocolParametersSubClassificationParameter = new Nbar2ProtocolParametersSubClassificationParameter ();

        prismAssert (NULL != pNbar2ProtocolParametersSubClassificationParameter, __FILE__, __LINE__);

        m_content.push_back (pNbar2ProtocolParametersSubClassificationParameter);

        return (pNbar2ProtocolParametersSubClassificationParameter);
    }
    else
    {
        return (Nbar2Element::getNbar2ElementByName (nbar2ElementName));
    }
}

}

