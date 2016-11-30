/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonString.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

JsonString::JsonString ()
    : JsonValue ()
{
}

JsonString::JsonString (const string &input)
    : JsonValue (),
      m_string (input)
{
}

JsonString::~JsonString ()
{
}

string JsonString::toString () const
{
    return ("\"" + m_string + "\"");
}

void JsonString::fromString (const string &input)
{
    string tempInput          = input;
    bool   successFullyLoaded = true;

    StringUtils::trimWhiteSpacesAtTheBeginingAndTheEnd (tempInput);

    if (0 < (tempInput.length ()))
    {
        if ('"' == tempInput[0])
        {
            tempInput.erase (0, 1);
        }
        else
        {
            successFullyLoaded = false;
        }
    }

    if (0 < (tempInput.length ()))
    {
        if ('"' == tempInput[tempInput.length () - 1])
        {
            tempInput.erase (tempInput.length () - 1, 1);
        }
        else
        {
            successFullyLoaded = false;
        }
    }

    m_string = tempInput;

    setSuccessFullyLoaded (successFullyLoaded);
}

void JsonString::print (const UI32 &level) const
{
    WaveNs::tracePrintf (TRACE_LEVEL_INFO, false, true, ("\"" + m_string + "\"").c_str ());
}

const string &JsonString::getString () const
{
    return (m_string);
}

}
