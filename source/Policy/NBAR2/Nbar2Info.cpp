/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2Info.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2Info::Nbar2Info ()
    : Nbar2Element ()
{
    addTextAttribute ("type", new AttributeString (&m_type));
    addTextAttribute ("file-version", new AttributeString (&m_fileVersion));

    addNbar2Element ("pp", &m_nbar2InfoPp);
}

Nbar2Info::~Nbar2Info ()
{
}

}

