/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONFALSE_H
#define JSONFALSE_H

#include "Framework/Types/Types.h"
#include "Modeling/JSON/ObjectModel/JsonValue.h"

namespace WaveNs
{

class JsonFalse : public JsonValue
{
    private :
    protected :
    public :
                           JsonFalse   ();
        virtual           ~JsonFalse   ();

        virtual string     toString    () const;
        virtual void       fromString  (const string &input);

        virtual void       print       (const UI32 &level)  const;

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // JSONFALSE_H
