/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONFACTORY_H
#define JSONFACTORY_H

#include <string>

using namespace std;

namespace WaveNs
{

class JsonValue;
class JsonObject;
class JsonArray;
class JsonPair;
class JsonString;
class JsonString;
class JsonNumber;
class JsonTrue;
class JsonFalse;
class JsonNull;

class JsonFactory
{
    private :
        JsonFactory ();

    protected :
    public :
        ~JsonFactory ();

        static JsonValue  *createJsonValueFromString (string &input);
        static JsonObject *createNewJsonObject       ();
        static JsonArray  *createNewJsonArray        ();
        static JsonPair   *createNewJsonPair         ();
        static JsonString *createNewJsonString       ();
        static JsonNumber *createNewJsonNumber       ();
        static JsonTrue   *createNewJsonTrue         ();
        static JsonFalse  *createNewJsonFalse        ();
        static JsonNull   *createJsonNull            ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // JSONFACTORY_H
