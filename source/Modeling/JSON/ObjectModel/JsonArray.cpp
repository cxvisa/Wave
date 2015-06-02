/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonArray.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Modeling/JSON/ObjectModel/JsonFactory/JsonFactory.h"
#include "Modeling/JSON/Utils/JsonToolKit.h"

namespace WaveNs
{

JsonArray::JsonArray ()
    : JsonValue ()
{
}

JsonArray::~JsonArray ()
{
}

string JsonArray::toString () const
{
    string output;
    UI32   numberOfJsonValues = m_jsonValues.size ();
    UI32   i                 = 0;

    output = "[";

    for (i = 0; i < numberOfJsonValues; i++)
    {
        output += (m_jsonValues[i])->toString ();

        if ((numberOfJsonValues - 1) != i)
        {
            output += ", ";
        }
    }

    output += "]";

    return (output);
}

void JsonArray::fromString (const string &input)
{
    string tempInput          = input;
    bool   successFullyLoaded = true;

    StringUtils::trimWhiteSpacesAtTheBeginingAndTheEnd (tempInput);

    if (('[' == tempInput[0]) && (']' == tempInput[(tempInput.length () - 1)]))
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
                JsonValue *pJsonValue = JsonFactory::createJsonValueFromString (level1Tokens[i]);

                m_jsonValues.push_back (pJsonValue);

                if (false == (pJsonValue->getSuccessFullyLoaded ()))
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

void JsonArray::print (const UI32 &level) const
{
    UI32   numberOfJsonValues = m_jsonValues.size ();
    UI32   i                 = 0;
    string space;

    tracePrintf (TRACE_LEVEL_INFO, false, true, "\r\n");

    for (i = 0; i < level; i++)
    {
        space += "  ";
    }

    tracePrintf (TRACE_LEVEL_INFO, false, true, "%s[\r\n", space.c_str ());

    for (i = 0; i < numberOfJsonValues; i++)
    {
        tracePrintf (TRACE_LEVEL_INFO, false, true, "%s  ", space.c_str ());

        m_jsonValues[i]->print (level + 1);

        if ((numberOfJsonValues - 1) != i)
        {
            tracePrintf (TRACE_LEVEL_INFO, false, true, ",\r\n");
        }
        else
        {
            tracePrintf (TRACE_LEVEL_INFO, false, true, "\r\n");
        }
    }

    tracePrintf (TRACE_LEVEL_INFO, false, true, (space + "]").c_str ());
}

}
