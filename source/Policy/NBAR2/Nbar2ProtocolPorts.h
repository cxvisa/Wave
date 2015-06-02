/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NBAR2PROTOCOLPORTS_H
#define NBAR2PROTOCOLPORTS_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Nbar2ProtocolPorts : public Nbar2Element
{
    private :
    protected :
    public :
                        Nbar2ProtocolPorts ();
        virtual        ~Nbar2ProtocolPorts ();

                UI64    getIp              () const;
                string  getTcp             () const;
                string  getUdp             () const;

    // Now the data elements

    private :
        UI64   m_ip;
        string m_udp;
        string m_tcp;

    protected :
    public :
};

}

#endif

