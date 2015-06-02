/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NBAR2PROTOCOL_H
#define NBAR2PROTOCOL_H

#include "Framework/Types/Types.h"
#include "Policy/NBAR2/Nbar2Element.h"
#include "Policy/NBAR2/Nbar2ProtocolAttributes.h"
#include "Policy/NBAR2/Nbar2ProtocolIpVersion.h"
#include "Policy/NBAR2/Nbar2ProtocolParameters.h"
#include "Policy/NBAR2/Nbar2ProtocolPorts.h"
#include "Policy/NBAR2/Nbar2ProtocolSignatureCounters.h"
#include "Policy/NBAR2/Nbar2ProtocolIndicativePorts.h"

namespace WaveNs
{

class Nbar2Protocol : public Nbar2Element
{
    private :
    protected :
    public :
                        Nbar2Protocol           ();
        virtual        ~Nbar2Protocol           ();

                string  getAdjustedCategoryName () const;

                string  getName                 () const;
                string  getCommonName           () const;
                bool    getEnabled              () const;
                UI64    getEngineId             () const;
                string  getGlobalId             () const;
                string  getHelpString           () const;
                UI64    getId                   () const;
                string  getLongDescription      () const;
                string  getReferences           () const;
                UI64    getSelectorId           () const;
                UI64    getCommonlyUsed         () const;

                const Nbar2ProtocolPorts           &getPorts           () const;
                const Nbar2ProtocolIndicativePorts &getIndicativePorts () const;
                const Nbar2ProtocolAttributes      &getAttributes      () const;

    // Now the data elements

    private :
        Nbar2ProtocolAttributes        m_attributes;
        string                         m_commonName;
        bool                           m_enabled;
        UI64                           m_engineId;
        string                         m_globalId;
        string                         m_helpString;
        UI64                           m_id;
        Nbar2ProtocolIpVersion         m_ipVersion;
        string                         m_longDescription;
        bool                           m_longDescriptionIsFinal;
        string                         m_name;
        Nbar2ProtocolParameters        m_parameters;
        UI64                           m_pdlVersion;
        Nbar2ProtocolPorts             m_ports;
        string                         m_references;
        UI64                           m_selectorId;
        Nbar2ProtocolSignatureCounters m_signatureCounters;
        Nbar2ProtocolIndicativePorts   m_indicativePorts;
        UI64                           m_commonlyUsed;
        string                         m_underlyingProtocols;
    protected :
    public :
};

}

#endif // NBAR2PROTOCOL_H

