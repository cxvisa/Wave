/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolSignatureCounters.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolSignatureCounters::Nbar2ProtocolSignatureCounters ()
{
    addNbar2Element ("heuristic-general-mp-tcp-handler", &m_heuristicGeneralMpTcpHandler);
    addNbar2Element ("heuristic-general-mp-udp-handler", &m_heuristicGeneralMpUdpHandler);

    addTextAttribute ("heuristic-general-udp-handler",       new AttributeUI64 (&m_heuristicGeneralUdpHandler));
    addTextAttribute ("heuristic-label-tcp-handler",         new AttributeUI64 (&m_heuristicLabelTcpHandler));
    addTextAttribute ("heuristic-regex-tcp-all-handler",     new AttributeUI64 (&m_heuristicRegexpTcpAllHandler));
    addTextAttribute ("heuristic-general-tcp-first-handler", new AttributeUI64 (&m_heuristicGeneralTcpFirstHandler));
    addTextAttribute ("heuristic-label-udp-handler",         new AttributeUI64 (&m_heuristicLabelUdpHandler));
    addTextAttribute ("heuristic-regexp-udp-handler",        new AttributeUI64 (&m_heuristicRegexpUdpHandler));
    addTextAttribute ("udp-well-known-port",                 new AttributeUI64 (&m_udpWellKnownPort));
    addTextAttribute ("tcp-well-known-port",                 new AttributeUI64 (&m_tcpWellKnownPort));
    addTextAttribute ("heuristic-regexp-tcp-first-handler",  new AttributeUI64 (&m_heuristicRegexpTcpFirstHandler));
    addTextAttribute ("heuristic-general-tcp-all-handler",   new AttributeUI64 (&m_heuristicGeneralTcpAllHandler));
}

Nbar2ProtocolSignatureCounters::~Nbar2ProtocolSignatureCounters ()
{
}

}

