/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonNull.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

JsonNull::JsonNull ()
    : JsonValue ()
{
    setSuccessFullyLoaded (true);
}

JsonNull::~JsonNull ()
{
}

string JsonNull::toString () const
{
    return ("null");
}

void JsonNull::fromString (const string &input)
{
}

void JsonNull::print (const UI32 &level) const
{
    tracePrintf (TRACE_LEVEL_INFO, false, true, "null");
}

}
