/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONNUMBER_H
#define JSONNUMBER_H

#include "Framework/Types/Types.h"
#include "Modeling/JSON/ObjectModel/JsonValue.h"
#include "Framework/Types/Number.h"

#include <string>

using namespace std;

namespace WaveNs
{

class JsonNumber : public JsonValue
{
    private :
    protected :
    public :
                        JsonNumber ();
                        JsonNumber (Number &number);
        virtual        ~JsonNumber ();

        virtual string  toString   () const;
        virtual void    fromString (const string &input);

        virtual void    print      (const UI32 &level) const;

        const Number &getNumber () const;

    // Now the data members

    private :
        Number m_number;

    protected :
    public :
};

}

#endif // JSONNUMBER_H
