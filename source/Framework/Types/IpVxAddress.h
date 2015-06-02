/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                            *
 ***************************************************************************/

#ifndef IPVXADDRESS_H
#define IPVXADDRESS_H

#include "Framework/Types/IpAddress.h"

namespace WaveNs
{

typedef enum
{
    WAVE_INVALID = 0,
    WAVE_IPV4,
    WAVE_IPV6
}IpType;

class IpVxAddress : public IpAddress
{
    private :

        void                   setIpType             (const IpType ipType);
        IpType                 determineIpType       (const string &ipVxAddress);
                              
    protected :               
    public :                  
                               IpVxAddress           ();
                               IpVxAddress           (const string &ipVxAddress);
                               IpVxAddress           (const IpVxAddress &ipVxAddress);
        virtual               ~IpVxAddress           ();
        virtual UI32           getAddressFamily      ();
        virtual void           fromString            (const string &ipVxAddress);
        virtual ResourceId     loadFromPlainString   (const string &ipVxAddress);
        bool                   operator ==           (const IpVxAddress &ipVxAddress) const;
        bool                   operator !=           (const IpVxAddress &ipVxAddress) const;
        IpVxAddress            &operator =           (const IpVxAddress &ipVxAddress);
        static bool            isValidIpV4Address    (const string &ipVxAddress);
        static bool            isValidIpV6Address    (const string &ipVxAddress);
        IpType                 getIpType             () const;

    // Now the data members

    private :
        IpType      m_addressType;

    protected :
    public :
};

}

#endif // IPVXADDRESS_H

