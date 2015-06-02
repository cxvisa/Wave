/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef IPV4ADDRESSNETWORKMASK_H
#define IPV4ADDRESSNETWORKMASK_H

#include "Framework/Types/IpAddressNetworkMask.h"

namespace WaveNs
{

class IpV4AddressNetworkMask : public IpAddressNetworkMask
{
    private :
                string       ipAddressToBinary           (const string ipAddress, bool inverse );
    protected :
    public :
                             IpV4AddressNetworkMask      ();
                             IpV4AddressNetworkMask      (const string &ipV4AddressNetworkMask);
                             IpV4AddressNetworkMask      (const IpV4AddressNetworkMask &ipV4AddressNetworkMask);
        virtual             ~IpV4AddressNetworkMask      ();
                            
        virtual UI32         getAddressFamily            ();
                ResourceId   loadFromPlainString         (const string &ipV4AddressNetworkMask);
                void         setInverseSubnetMask        (bool inverseSubnetMask);
                bool         getInverseSubnetMask        ();
    // Now the data members

    private :
        bool m_inverseSubnetMask;
    protected :
    public :
};

}

#endif // IPV4ADDRESSNETWORKMASK_H

