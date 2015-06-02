/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/Utils/JsonToolKit.h"

namespace WaveNs
{

bool JsonToolKit::splitJsonValueString (const string &input, vector<string> &jsonValueStrings)
{
    const char              separatorCharacter    = ',';
          bool              insideStringQuotes    = false;
          string::size_type startPosition         = 0;
    const string::size_type stringLength          = input.size ();
          char              previousCharacter     = '\0';
          char              currentCharacter      = '\0';
          UI32              jsonValueDepth        = 0;
          UI32              previousStartPosition = 0;
          string            token;

    while (stringLength > startPosition )
    {
        currentCharacter = input[startPosition];

        if (true == insideStringQuotes)
        {
            if (('"' == currentCharacter) && ('\\' != previousCharacter))
            {
                insideStringQuotes = false;
            }
        }
        else
        {
            if (('"' == currentCharacter) && ('\\' != previousCharacter))
            {
                insideStringQuotes = true;
            }
            else
            {
                if (('{' == currentCharacter) || ('[' == currentCharacter))
                {
                    jsonValueDepth++;
                }
                else if (('}' == currentCharacter) || (']' == currentCharacter))
                {
                    if (0 == jsonValueDepth)
                    {
                        // Erroneous JSON Input.  Return doing nothing.

                        return (false);
                    }

                    jsonValueDepth--;
                }
                else if (separatorCharacter == currentCharacter)
                {
                    if (0 == jsonValueDepth)
                    {
                        token = input.substr (previousStartPosition, startPosition - previousStartPosition);

                        jsonValueStrings.push_back (token);

                        previousStartPosition = startPosition + 1;
                    }
                }
            }
        }

        previousCharacter = currentCharacter;
        startPosition++;
    }

    if (startPosition > previousStartPosition)
    {
        token = input.substr (previousStartPosition, startPosition - previousStartPosition);

        jsonValueStrings.push_back (token);
    }

    return (true);
}

}
