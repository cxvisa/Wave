/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonObject.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Modeling/JSON/ObjectModel/JsonPair.h"
#include "Modeling/JSON/Utils/JsonToolKit.h"

namespace WaveNs
{

JsonObject::JsonObject ()
    : JsonValue ()
{
}

JsonObject::~JsonObject ()
{
}

string JsonObject::toString () const
{
    string output;
    UI32   numberOfJsonPairs = m_jsonPairs.size ();
    UI32   i                 = 0;

    output = "{";

    for (i = 0; i < numberOfJsonPairs; i++)
    {
        output += (m_jsonPairs[i])->toString ();

        if ((numberOfJsonPairs - 1) != i)
        {
            output += ",";
        }
    }

    output += "}";

    return (output);
}

void JsonObject::fromString (const string &input)
{
    string tempInput          = input;
    bool   successFullyLoaded = true;

    StringUtils::trimWhiteSpacesAtTheBeginingAndTheEnd (tempInput);

    if (('{' == tempInput[0]) && ('}' == tempInput[(tempInput.length () - 1)]))
    {
        tempInput.erase (0, 1);
        tempInput.erase (tempInput.length () - 1, 1);

        vector<string> level1Tokens;

        bool successFullySplit = JsonToolKit::splitJsonValueString (tempInput, level1Tokens);

        if (true == successFullySplit)
        {
            UI32 numberOfLevel1Tokens = level1Tokens.size ();
            UI32 i                   = 0;

            for (i = 0; i < numberOfLevel1Tokens; i++)
            {
                JsonPair *pJsonPair = new JsonPair ();

                prismAssert (NULL != pJsonPair, __FILE__, __LINE__);

                pJsonPair->fromString (level1Tokens[i]);

                m_jsonPairs.push_back (pJsonPair);

                if (false == (pJsonPair->getSuccessFullyLoaded ()))
                {
                    successFullyLoaded = false;
                }
            }
        }
        else
        {
            successFullyLoaded = false;
        }
    }
    else
    {
        successFullyLoaded = false;
    }

    setSuccessFullyLoaded (successFullyLoaded);
}

void JsonObject::print (const UI32 &level) const
{
    UI32   numberOfJsonPairs = m_jsonPairs.size ();
    UI32   i                 = 0;
    string space;

    tracePrintf (TRACE_LEVEL_INFO, false, true, "\r\n");

    for (i = 0; i < level; i++)
    {
        space += "  ";
    }

    tracePrintf (TRACE_LEVEL_INFO, false, true, "%s{\r\n", space.c_str ());

    for (i = 0; i < numberOfJsonPairs; i++)
    {
        (m_jsonPairs[i])->print (level + 1);

        if ((numberOfJsonPairs - 1) != i)
        {
            tracePrintf (TRACE_LEVEL_INFO, false, true, ",\r\n");
        }
        else
        {
            tracePrintf (TRACE_LEVEL_INFO, false, true, "\r\n");
        }
    }

    tracePrintf (TRACE_LEVEL_INFO, false, true, (space + "}").c_str ());
}

}
