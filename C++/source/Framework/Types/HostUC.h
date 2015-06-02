/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef HOSTUC_H
#define HOSTUC_H

#include "Framework/Types/IpV4Address.h"
#include "Framework/Types/IpV6Address.h"

namespace WaveNs
{

typedef enum 
{
    WAVE_DOMAINNAME = 0,
    WAVE_IPV4ADDRESS,
    WAVE_IPV6ADDRESS,
    WAVE_UNKNOWN_HOSTTYPE
} HostType;

class HostUC
{
    private :
    protected :
    public :
                            HostUC                     ();
                            HostUC                     (const string &domainName);
                            HostUC                     (const string &domainName, const bool &isUserConfigured);
                            HostUC                     (const IpV4Address &ipV4Address);
                            HostUC                     (const IpV4Address &ipV4Address, const bool &isUserConfigured);
                            HostUC                     (const IpV6Address &ipV6Address);
                            HostUC                     (const IpV6Address &ipV6Address, const bool &isUserConfigured);
                            HostUC                     (const HostUC &hostUC);
        virtual            ~HostUC                     ();

                void        setHostValue               (const string &pDomainName);
                void        setHostValue               (const IpV4Address &ipV4Address);
                void        setHostValue               (const IpV6Address &ipV6Address);
                string      getHostValue               () const;
                HostType    getHostType                () const;

                bool        isValidIpV4Address         (const string &ipV4Address);
                bool        isValidIpV6Address         (const string &ipV6Address);
        virtual UI32        getAddressFamily           ();

                void        setIsUserConfigured        (const bool &isUserConfigured);
                bool        getIsUserConfigured        () const;

                void        toString                   (string &valueString) const;
                void        fromString                 (const string &hostAsString);

        virtual void        getPlainString             (string &valueString) const;
                ResourceId  loadFromPlainString        (const string &pHostUCInPlainStringFormat);

                bool        operator == (const HostUC &pHostUC)  const;
                bool        operator != (const HostUC &pHostUC)  const;
                HostUC     &operator  = (const HostUC &pHostUC);

    // Now the data members

    private :
       string      m_domainName;
       IpV4Address m_ipV4Address;
       IpV6Address m_ipV6Address;
       HostType    m_hostType;
       bool        m_pIsUserConfigured;
};

}

#endif // HOSTUC_H
