/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "Framework/Types/Types.h"
#include <string>

namespace WaveNs
{

class BigInteger
{
    private :
    protected :
    public :
                BigInteger         (const SI64 &bigIntegerValue);
               ~BigInteger         ();

        SI64    getIntegerValue ()                                const;
        void    setIntegerValue (const SI64 &bigIntegerValue);
        string  toString        ()                                const;
        string  toHexString     ()                                const;

    // Now the data members

    private :
        SI64 m_bigIntegerValue;

    protected :
    public :
};

}

#endif // BIGINTEGER_H
