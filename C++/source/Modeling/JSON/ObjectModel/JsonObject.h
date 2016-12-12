/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "Modeling/JSON/ObjectModel/JsonValue.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class JsonPair;

class JsonObject : public JsonValue
{
    private :
    protected :
    public :
                                    JsonObject      ();
        virtual                    ~JsonObject      ();

        virtual string              toString        () const;
        virtual void                fromString      (const string &input);

        virtual void                print           (const UI32 &level = 0) const;

                JsonValue          *getValueForName (const string &name);

                bool                isAKnownName    (const string &name) const;

                vector<JsonPair *> &getJsonPairs    ();

    // Now the data members

    private :
        vector<JsonPair *>       m_jsonPairs;
        map<string, JsonValue *> m_valuesByName;

    protected :
    public :
};

}

#endif // JSONOBJECT_H
