/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H

#include "Framework/Types/IpAddress.h"

namespace WaveNs
{

class IpV6Address : public IpAddress
{
    private :
    protected :
    public :
                               IpV6Address             ();
                               IpV6Address             (const string &ipV6Address);
                               IpV6Address             (const IpV6Address &ipV6Address);
        virtual               ~IpV6Address             ();
                                                       
        virtual UI32           getAddressFamily        ();
        virtual ResourceId     loadFromPlainString     (const string &valueString);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // IPV6ADDRESS_H
