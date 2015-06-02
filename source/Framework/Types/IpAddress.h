/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef IPADDRESS_H
#define IPADDRESS_H

#include "Framework/Types/Types.h"
#include <string>

using namespace std;

namespace WaveNs
{

class IpAddress
{
    private :
    protected :
    public :
                               IpAddress              ();
                               IpAddress              (const string &ipAddress);
                               IpAddress              (const IpAddress &ipAddress);
        virtual               ~IpAddress              ();
                                                      
        virtual UI32           getAddressFamily       () = 0;
                string         toString               () const;
                void           fromString             (const string &ipAddress);
        virtual ResourceId     loadFromPlainString    (const string &ipAddress);
                                                      
                bool           operator ==            (const IpAddress &ipAddress) const;
                bool           operator !=            (const IpAddress &ipAddress) const;
                IpAddress     &operator =             (const IpAddress &ipAddress);
                
    // now the data members

    private :
        string m_ipAddress;

    protected :
    public :
};

}

#endif // IPADDRESS_H
