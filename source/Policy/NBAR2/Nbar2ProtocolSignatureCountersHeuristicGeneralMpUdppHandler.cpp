/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler::Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler ()
    : Nbar2Element ()
{
    addTextAttribute ("main",      new AttributeUI64 (&m_main));
    addTextAttribute ("recursive", new AttributeUI64 (&m_recursive));
}

Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler::~Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler ()
{
}

}

