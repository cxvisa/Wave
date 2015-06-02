/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLSIGNATURECOUNTERS_H
#define NBAR2PROTOCOLSIGNATURECOUNTERS_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Policy/NBAR2/Nbar2ProtocolSignatureCountersHeuristicGeneralMpTcpHandler.h"
#include "Policy/NBAR2/Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Nbar2ProtocolSignatureCounters : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2ProtocolSignatureCounters ();
        virtual ~Nbar2ProtocolSignatureCounters ();

    // Now the data elements

    private :
        UI64                                                       m_heuristicGeneralUdpHandler;
        UI64                                                       m_heuristicLabelTcpHandler;
        UI64                                                       m_heuristicRegexpTcpAllHandler;
        Nbar2ProtocolSignatureCountersHeuristicGeneralMpTcpHandler m_heuristicGeneralMpTcpHandler;
        UI64                                                       m_heuristicGeneralTcpFirstHandler;
        UI64                                                       m_heuristicLabelUdpHandler;
        UI64                                                       m_heuristicRegexpUdpHandler;
        UI64                                                       m_udpWellKnownPort;
        Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler m_heuristicGeneralMpUdpHandler;
        UI64                                                       m_tcpWellKnownPort;
        UI64                                                       m_heuristicRegexpTcpFirstHandler;
        UI64                                                       m_heuristicGeneralTcpAllHandler;
    protected :
    public :
};

}

#endif

