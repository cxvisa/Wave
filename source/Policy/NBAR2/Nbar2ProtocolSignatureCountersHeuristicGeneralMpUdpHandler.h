/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLSIGNATURECOUNTERSHEURISTICGENERALMPUDPHANDLER_H
#define NBAR2PROTOCOLSIGNATURECOUNTERSHEURISTICGENERALMPUDPHANDLER_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler ();
        virtual ~Nbar2ProtocolSignatureCountersHeuristicGeneralMpUdpHandler ();

    // Now the data elements

    private :
        UI64 m_main;
        UI64 m_recursive;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLSIGNATURECOUNTERSHEURISTICGENERALMPUDPHANDLER_H

