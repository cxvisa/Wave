/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONSTRING_H
#define JSONSTRING_H

#include "Framework/Types/Types.h"
#include "Modeling/JSON/ObjectModel/JsonValue.h"

#include <string>

using namespace std;

namespace WaveNs
{

class JsonString : public JsonValue
{
    private :
    protected :
    public :
                        JsonString ();
                        JsonString (const string &input);
        virtual        ~JsonString ();

        virtual string  toString   () const;
        virtual void    fromString (const string &input);

        virtual void    print      (const UI32 &level) const;

    // Now the data members

    private :
        string m_string;

    protected :
    public :
};

}

#endif // JSONSTRING_H
