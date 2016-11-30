/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONPAIR_H
#define JSONPAIR_H

#include "Framework/Types/Types.h"
#include "Modeling/JSON/ObjectModel/JsonValue.h"

#include <string>
#include <utility>

using namespace std;

namespace WaveNs
{

class JsonPair : public JsonValue
{
    private :
    protected :
    public :
                        JsonPair   ();
                        JsonPair   (string &name, JsonValue *pValue);
        virtual        ~JsonPair   ();

        virtual string  toString   () const;
        virtual void    fromString (const string &input);
        virtual void    print      (const UI32 &level = 0) const;

        const string    &getName   () const;
              JsonValue *getPValue ();

    // Now the data members

    private :
        string     m_name;
        JsonValue *m_pValue;

    protected :
    public :
};

}

#endif // JSONPAIR_H
