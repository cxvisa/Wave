/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NBAR2PROTOCOLINDICATIVEPORTS_H
#define NBAR2PROTOCOLINDICATIVEPORTS_H

#include "Policy/NBAR2/Nbar2Element.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Nbar2ProtocolIndicativePorts : public Nbar2Element
{
    private :
    protected :
    public :
                         Nbar2ProtocolIndicativePorts ();
        virtual         ~Nbar2ProtocolIndicativePorts ();

                UI64     getIp                        () const;
                string   getTcp                       () const;
                string   getUdp                       () const;

    // Now the data elements

    private :
        UI64   m_ip;
        string m_udp;
        string m_tcp;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLINDICATIVEPORTS_H

