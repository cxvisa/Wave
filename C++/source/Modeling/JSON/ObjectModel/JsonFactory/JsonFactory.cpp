/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonFactory/JsonFactory.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Modeling/JSON/ObjectModel/JsonArray.h"
#include "Modeling/JSON/ObjectModel/JsonObject.h"
#include "Modeling/JSON/ObjectModel/JsonPair.h"
#include "Modeling/JSON/ObjectModel/JsonNumber.h"
#include "Modeling/JSON/ObjectModel/JsonTrue.h"
#include "Modeling/JSON/ObjectModel/JsonFalse.h"
#include "Modeling/JSON/ObjectModel/JsonNull.h"
#include "Modeling/JSON/ObjectModel/JsonString.h"

namespace WaveNs
{

JsonValue  *JsonFactory::createJsonValueFromString (string &input)
{
    StringUtils::trimWhiteSpacesAtTheBeginingAndTheEnd (input);

    if (0 == (input.size ()))
    {
        return (NULL);
    }

    const char firstCharacter = input[0];

    if ('[' == firstCharacter)
    {
        JsonArray *pJsonArray = new JsonArray ();

        prismAssert (NULL != pJsonArray, __FILE__, __LINE__);

        pJsonArray->fromString (input);

        return (pJsonArray);
    }
    else if ('{' == firstCharacter)
    {
        JsonObject *pJsonObject = new JsonObject ();

        prismAssert (NULL != pJsonObject, __FILE__, __LINE__);

        pJsonObject->fromString (input);

        return (pJsonObject);
    }
    else if ('"' == firstCharacter)
    {
        JsonString *pJsonString = new JsonString ();

        prismAssert (NULL != pJsonString, __FILE__, __LINE__);

        pJsonString->fromString (input);

        return (pJsonString);
    }
    else
    {
        string inputInUpperCase = input;

        StringUtils::convertToUpperCase (inputInUpperCase);

        if ("TRUE" == inputInUpperCase)
        {
            return (new JsonTrue ());
        }
        else if ("FALSE" == inputInUpperCase)
        {
            return (new JsonFalse ());
        }
        else if ("NULL" == inputInUpperCase)
        {
            return (new JsonNull ());
        }
        else if (true == (Number::isAValidNumber(inputInUpperCase)))
        {
            JsonNumber *pJsonNumber = new JsonNumber ();

            prismAssert (NULL != pJsonNumber, __FILE__, __LINE__);

            pJsonNumber->fromString (input);

            return (pJsonNumber);
        }
    }

    return (NULL);
}

JsonObject *JsonFactory::createNewJsonObject ()
{
    return (new JsonObject ());
}

JsonArray *JsonFactory::createNewJsonArray ()
{
    return (new JsonArray ());
}

JsonPair *JsonFactory::createNewJsonPair ()
{
    return (new JsonPair ());
}

JsonString *JsonFactory::createNewJsonString ()
{
    return (new JsonString ());
}

JsonNumber *JsonFactory::createNewJsonNumber ()
{
    return (new JsonNumber ());
}

JsonTrue *JsonFactory::createNewJsonTrue ()
{
    return (new JsonTrue ());
}

JsonFalse *JsonFactory::createNewJsonFalse ()
{
    return (new JsonFalse ());
}

JsonNull *JsonFactory::createJsonNull ()
{
    return (new JsonNull ());
}

}
