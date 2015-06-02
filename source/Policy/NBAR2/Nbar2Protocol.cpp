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

Nbar2Protocol::Nbar2Protocol ()
    : Nbar2Element ()
{
    addNbar2Element ("attributes",         &m_attributes);
    addNbar2Element ("ip-version",         &m_ipVersion);
    addNbar2Element ("parameters",         &m_parameters);
    addNbar2Element ("ports",              &m_ports);
    addNbar2Element ("signature-counters", &m_signatureCounters);
    addNbar2Element ("indicative-ports",   &m_indicativePorts);

    addTextAttribute ("common-name",                   new AttributeString (&m_commonName));
    addTextAttribute ("enabled",                       new AttributeBool   (&m_enabled));
    addTextAttribute ("engine-id",                     new AttributeUI64   (&m_engineId));
    addTextAttribute ("global-id",                     new AttributeString (&m_globalId));
    addTextAttribute ("help-string",                   new AttributeString (&m_helpString));
    addTextAttribute ("id",                            new AttributeUI64   (&m_id));
    addTextAttribute ("long-description",              new AttributeString (&m_longDescription));
    addTextAttribute ("long-description-is-final",     new AttributeBool   (&m_longDescriptionIsFinal));
    addTextAttribute ("name",                          new AttributeString (&m_name));
    addTextAttribute ("pdl-version",                   new AttributeUI64   (&m_pdlVersion));
    addTextAttribute ("references",                    new AttributeString (&m_references));
    addTextAttribute ("selector-id",                   new AttributeUI64   (&m_selectorId));
    addTextAttribute ("commonly-used",                 new AttributeUI64   (&m_commonlyUsed));
    addTextAttribute ("underlying-protocols",          new AttributeString (&m_underlyingProtocols));
}

Nbar2Protocol::~Nbar2Protocol ()
{
}

string Nbar2Protocol::getAdjustedCategoryName () const
{
    return (m_attributes.getAdjustedCategoryName ());
}

string Nbar2Protocol::getName () const
{
    return (m_name);
}

string Nbar2Protocol::getCommonName () const
{
    return (m_commonName);
}
bool Nbar2Protocol::getEnabled () const
{
    return (m_enabled);
}

UI64 Nbar2Protocol::getEngineId () const
{
    return (m_engineId);
}

string Nbar2Protocol::getGlobalId () const
{
    return (m_globalId);
}

string Nbar2Protocol::getHelpString () const
{
    return (m_helpString);
}

UI64 Nbar2Protocol::getId () const
{
    return (m_id);
}

const Nbar2ProtocolPorts &Nbar2Protocol::getPorts () const
{
    return (m_ports);
}

string Nbar2Protocol::getLongDescription () const
{
    return (m_longDescription);
}

string Nbar2Protocol::getReferences () const
{
    return (m_references);
}

UI64 Nbar2Protocol::getSelectorId () const
{
    return (m_selectorId);
}

UI64 Nbar2Protocol::getCommonlyUsed () const
{
    return (m_commonlyUsed);
}

const Nbar2ProtocolIndicativePorts &Nbar2Protocol::getIndicativePorts () const
{
    return (m_indicativePorts);
}

const Nbar2ProtocolAttributes &Nbar2Protocol::getAttributes () const
{
    return (m_attributes);
}

}

