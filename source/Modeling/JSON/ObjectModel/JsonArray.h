/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "Modeling/JSON/ObjectModel/JsonValue.h"

namespace WaveNs
{

class JsonArray : public JsonValue
{
    private :
    protected :
    public :
                        JsonArray  ();
        virtual        ~JsonArray  ();

        virtual string  toString   () const;
        virtual void    fromString (const string &input);

        virtual void    print      (const UI32 &level) const;

    // Now the data members

    private :
        vector<JsonValue *> m_jsonValues;

    protected :
    public :
};

}

#endif // JSONARRAY_H
