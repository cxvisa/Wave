/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2ProtocolSignatureCountersHeuristicGeneralMpTcpHandler.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

Nbar2ProtocolSignatureCountersHeuristicGeneralMpTcpHandler::Nbar2ProtocolSignatureCountersHeuristicGeneralMpTcpHandler ()
    : Nbar2Element ()
{
    addTextAttribute ("main",      new AttributeUI64 (&m_main));
    addTextAttribute ("recursive", new AttributeUI64 (&m_recursive));
}

Nbar2ProtocolSignatureCountersHeuristicGeneralMpTcpHandler::~Nbar2ProtocolSignatureCountersHeuristicGeneralMpTcpHandler ()
{
}

}

