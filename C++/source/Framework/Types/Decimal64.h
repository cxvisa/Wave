/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef DECIMAL64_H
#define DECIMAL64_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Decimal64
{

    private:
    protected:
    public:
                         Decimal64             ();
                         Decimal64             (const string &decimal64InStringFormat);
                         Decimal64             (const Decimal64 &decimal64);
                        ~Decimal64             ();
                                               
        string           toString              ()                                             const;
        void             fromString            (const string &decimal64InStringFormat);
        ResourceId       loadFromPlainString   (const string &decimal64InStringFormat);
                                               
        bool             operator ==           (const Decimal64 &decimal64)                   const;
        bool             operator !=           (const Decimal64 &decimal64)                   const;
        Decimal64       &operator =            (const Decimal64 &decimal64);
                                               
        SI64             getVal                ()                                             const;
        UI8              getFractionDigits     ()                                             const;   // indicates where to put '.' in val above
        void             setAllValues          (SI64 val, UI8 fractiondigits);

    // Now the data members
    private:
        SI64        m_val;
        UI8         m_fractionDigits;   // indicates where to put '.' in val above
                                        // e.g. 24957.54 implies val=2495754 & fraction=2
    protected:
    public:
};

}

#endif //DECIMAL64_H
