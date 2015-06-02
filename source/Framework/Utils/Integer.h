/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef INTEGER_H
#define INTEGER_H

#include "Framework/Types/Types.h"
#include <string>

namespace WaveNs
{

class Integer
{
    private :
    protected :
    public :
                Integer         (const SI32 &integerValue);
               ~Integer         ();

        SI32    getIntegerValue ()                          const;
        void    setIntegerValue (const SI32 &integerValue);
        string  toString        ()                          const;
        string  toHexString     ()                          const;

    // Now the data members

    private :
        SI32 m_integerValue;

    protected :
    public :
};

}

#endif // INTEGER_H
