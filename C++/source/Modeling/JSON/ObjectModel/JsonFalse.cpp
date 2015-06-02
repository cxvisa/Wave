/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonFalse.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

JsonFalse::JsonFalse ()
    : JsonValue ()
{
    setSuccessFullyLoaded (true);
}

JsonFalse::~JsonFalse ()
{
}

string JsonFalse::toString () const
{
    return ("false");
}

void JsonFalse::fromString (const string &input)
{
}

void JsonFalse::print (const UI32 &level) const
{
    tracePrintf (TRACE_LEVEL_INFO, false, true, "false");
}

}
