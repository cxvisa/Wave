/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2Protocol.h"
#include "Framework/Attributes/Attributes.h"
#include "Policy/NBAR2/Nbar2.h"

namespace WaveNs
{

Nbar2ProtocolAttributes::Nbar2ProtocolAttributes ()
    : Nbar2Element ()
{
    addTextAttribute ("application-group", new AttributeString (&m_applicationGroup));
    addTextAttribute ("category",          new AttributeString (&m_category));
    addTextAttribute ("encrypted",         new AttributeString (&m_encrypted));
    addTextAttribute ("p2p-technology",    new AttributeString (&m_p2pTechnology));
    addTextAttribute ("sub-category",      new AttributeString (&m_subCategory));
    addTextAttribute ("tunnel",            new AttributeString (&m_tunnel));
}

Nbar2ProtocolAttributes::~Nbar2ProtocolAttributes ()
{
}

string Nbar2ProtocolAttributes::getCategory () const
{
    return (m_category);
}

string Nbar2ProtocolAttributes::getSubCategory () const
{
    return (m_subCategory);
}

string Nbar2ProtocolAttributes::getAdjustedCategoryName () const
{
    return (Nbar2::getAdjustedCategoryName (getCategory (), getSubCategory ()));
}

string Nbar2ProtocolAttributes::getApplicationGroup () const
{
    return (m_applicationGroup);
}

string Nbar2ProtocolAttributes::getEncrypted () const
{
    return (m_encrypted);
}

string Nbar2ProtocolAttributes::getP2pTechnology () const
{
    return (m_p2pTechnology);
}
string Nbar2ProtocolAttributes::getTunnel () const
{
    return (m_tunnel);
}


}
