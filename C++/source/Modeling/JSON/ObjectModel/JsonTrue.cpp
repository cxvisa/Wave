/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonTrue.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

JsonTrue::JsonTrue ()
    : JsonValue ()
{
    setSuccessFullyLoaded (true);
}

JsonTrue::~JsonTrue ()
{
}

string JsonTrue::toString () const
{
    return ("true");
}

void JsonTrue::fromString (const string &input)
{
}

void JsonTrue::print (const UI32 &level) const
{
    tracePrintf (TRACE_LEVEL_INFO, false, true, "true");
}

}
