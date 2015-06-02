/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2PROTOCOLIPVERSION_H
#define NBAR2PROTOCOLIPVERSION_H

#include "Policy/NBAR2/Nbar2Element.h"

namespace WaveNs
{

class Nbar2ProtocolIpVersion : public Nbar2Element
{
    private :
    protected :
    public :
                 Nbar2ProtocolIpVersion ();
        virtual ~Nbar2ProtocolIpVersion ();

    // Now the data elements

    private :
        bool m_ipv4;
        bool m_ipv6;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLIPVERSION_H

