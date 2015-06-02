/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2InfoPp.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2InfoPp::Nbar2InfoPp ()
    : Nbar2Element ()
{
    addTextAttribute ("type",           new AttributeString (&m_type));
    addTextAttribute ("pp-version",     new AttributeString (&m_ppVersion));
    addTextAttribute ("ios-version",    new AttributeString (&m_iosVersion));
    addTextAttribute ("platform",       new AttributeString (&m_platform));
    addTextAttribute ("engine-version", new AttributeUI64   (&m_engineVersion));
}


Nbar2InfoPp::~Nbar2InfoPp ()
{
}

}

