/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef IPADDRESSNETWORKMASK_H
#define IPADDRESSNETWORKMASK_H

#include "Framework/Types/Types.h"
#include <string>

using namespace std;

namespace WaveNs
{

class IpAddressNetworkMask
{
    private :
                  void    parseNetworkMask        (string &ipAddressNetworkMask); 
    protected :  
    public :      
                                         IpAddressNetworkMask    ();
                                         IpAddressNetworkMask    (const string &ipAddressNetworkMask);
                                         IpAddressNetworkMask    (const IpAddressNetworkMask &ipAddressNetworkMask);
        virtual                         ~IpAddressNetworkMask    ();
                  
        virtual   UI32                   getAddressFamily        () = 0;
                  string                 toString                () const;
                  void                   fromString              (const string &ipAddressNetworkMask);
                  string                 getIpAddress            () const;
                  void                   setIpAddress            (const string &ipAddress) ;
                  UI8                    getLength               () const;
                  void                   setLength               (const UI8 &length) ;
                  void                   getPlainString          (string &valueString) const;
        virtual   ResourceId             loadFromPlainString     (const string &ipAddressNetworkMask);
                  
                  bool                   operator ==             (const IpAddressNetworkMask &ipAddressNetworkMask) const;
                  bool                   operator !=             (const IpAddressNetworkMask &ipAddressNetworkMask) const;
                  IpAddressNetworkMask  &operator =              (const IpAddressNetworkMask &ipAddressNetworkMask);
                

    // now the data members

    private :
        string m_ipAddress;
        UI8    m_len;

    protected :
    public :
};

}

#endif // IPADDRESSNETWORKMASK_H
