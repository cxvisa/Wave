/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "Modeling/JSON/ObjectModel/JsonValue.h"

#include <string>

using namespace std;

namespace WaveNs
{

class JsonPair;

class JsonObject : public JsonValue
{
    private :
    protected :
    public :
                        JsonObject ();
        virtual        ~JsonObject ();

        virtual string  toString   () const;
        virtual void    fromString (const string &input);

        virtual void    print      (const UI32 &level = 0) const;

    // Now the data members

    private :
        vector<JsonPair *> m_jsonPairs;

    protected :
    public :
};

}

#endif // JSONOBJECT_H
