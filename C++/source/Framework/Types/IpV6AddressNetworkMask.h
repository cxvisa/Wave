/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef IPV6ADDRESSNETWORKMASK_H
#define IPV6ADDRESSNETWORKMASK_H

#include "Framework/Types/IpAddressNetworkMask.h"

namespace WaveNs
{

class IpV6AddressNetworkMask : public IpAddressNetworkMask
{
    private :
    protected :
    public :
                             IpV6AddressNetworkMask      ();
                             IpV6AddressNetworkMask      (const string &ipV6AddressNetworkMask);
                             IpV6AddressNetworkMask      (const IpV6AddressNetworkMask &ipV6AddressNetworkMask);
        virtual             ~IpV6AddressNetworkMask      ();
                            
        virtual UI32         getAddressFamily            ();
        virtual ResourceId   loadFromPlainString         (const string &ipV6AddressNetworkMask);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // IPV6ADDRESSNETWORKMASK_H

