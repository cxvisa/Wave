/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonNumber.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

JsonNumber::JsonNumber ()
    : JsonValue ()
{
}

JsonNumber::JsonNumber (Number &number)
    : JsonValue (),
      m_number  (number)
{
}

JsonNumber::~JsonNumber ()
{
}

string JsonNumber::toString () const
{
    return (m_number.toString ());
}

void JsonNumber::fromString (const string &input)
{
    if (true == (Number::isAValidNumber (input)))
    {
        m_number.fromString (input);

        setSuccessFullyLoaded (true);
    }
    else
    {
        setSuccessFullyLoaded (false);
    }
}

void JsonNumber::print (const UI32 &level) const
{
    tracePrintf (TRACE_LEVEL_INFO, false, true, "%LF", m_number.getLd ());
}

const Number &JsonNumber::getNumber () const
{
    return (m_number);
}

}
