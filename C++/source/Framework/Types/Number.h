/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NUMBER_H
#define NUMBER_H

#include "Framework/Types/Types.h"

#include <string>

using namespace std;

namespace WaveNs
{

class Number
{
    private :
    protected :
    public :
                      Number         ();
                      Number         (const string &numberInStringFormat);
                      Number         (const LD &ld);
                      Number         (const Number &number);
                     ~Number         ();

       static bool    isAValidNumber (const string &numberInStringFormat);

              string  toString       () const;
              void    fromString     (const string &numberInStringFormat);

              LD      getLd          () const;
              void    setLd          (const LD &ld);

              Number &operator =     (const Number &number);
              bool    operator !=    (const Number &number);
              bool    operator ==    (const Number &number);
              bool    operator >     (const Number &number);
              bool    operator >=    (const Number &number);
              bool    operator <     (const Number &number);
              bool    operator <=    (const Number &number);

    // Now the data members

    private :
        LD m_ld;

    protected :
    public :
};

}

#endif // NUMBER_H
