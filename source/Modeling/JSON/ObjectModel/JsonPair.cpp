/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonPair.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Modeling/JSON/ObjectModel/JsonFactory/JsonFactory.h"

namespace WaveNs
{

JsonPair::JsonPair ()
    : JsonValue (),
      m_pValue (NULL)
{
}

JsonPair::JsonPair (string &name, JsonValue *pValue)
    : JsonValue (),
      m_name    (name),
      m_pValue  (pValue)
{
}

JsonPair::~JsonPair ()
{
    if (NULL != m_pValue)
    {
        delete m_pValue;
    }
}

string JsonPair::toString () const
{
    string tempString;

    tempString = "\"" + m_name + "\" : ";

    if (NULL != m_pValue)
    {
        tempString += m_pValue->toString ();
    }
    else
    {
        tempString += "N U L L";
    }

    return (tempString);
}

void JsonPair::fromString (const string &input)
{
    string tempInput = input;

    StringUtils::trimWhiteSpacesAtTheBeginingAndTheEnd (tempInput);

    string name;
    string value;
    bool   successFullyLoaded = false;

    StringUtils::splitBasedOnFirstOccuranceOfConsideringStringQuotes (tempInput, ':', name, value);

    StringUtils::trimWhiteSpacesAtTheBeginingAndTheEnd (name);
    StringUtils::trimWhiteSpacesAtTheBeginingAndTheEnd (value);

    JsonValue *pJsonValue = JsonFactory::createJsonValueFromString (value);

    if (NULL != pJsonValue)
    {
        if (0 < (name.length ()))
        {
            if ('"' == name[0])
            {
                name.erase (0, 1);
            }
        }

        if (0 < (name.length ()))
        {
            if ('"' == name[name.length () - 1])
            {
                name.erase (name.length () - 1, 1);
            }
        }

        m_name   = name;
        m_pValue = pJsonValue;

        if (true == (pJsonValue->getSuccessFullyLoaded ()))
        {
            successFullyLoaded = true;
        }
    }

    setSuccessFullyLoaded (successFullyLoaded);
}

void JsonPair::print (const UI32 &level) const
{
    string tempString;
    string space;
    UI32   i           = 0;

    for (i = 0; i < level; i++)
    {
        space += "  ";
    }

    tracePrintf (TRACE_LEVEL_INFO, false, true, (space + "\"" + m_name + "\" : ").c_str ());

    if (NULL != m_pValue)
    {
        m_pValue->print (level + 1);
    }
    else
    {
        tracePrintf (TRACE_LEVEL_INFO, false, true, "N U L L");
    }
}

}
