/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include "Framework/Types/IpAddress.h"

namespace WaveNs
{

class IpV4Address : public IpAddress
{
    private :
    protected :
    public :
                               IpV4Address             ();
                               IpV4Address             (const string &ipV4Address);
                               IpV4Address             (const IpV4Address &ipV4Address);
        virtual               ~IpV4Address             ();
                                                       
        virtual UI32           getAddressFamily        ();
        virtual ResourceId     loadFromPlainString     (const string &valueString);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // IPV4ADDRESS_H
