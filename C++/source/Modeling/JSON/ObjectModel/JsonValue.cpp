/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/JSON/ObjectModel/JsonValue.h"

namespace WaveNs
{

JsonValue::JsonValue ()
    : m_successFullyLoaded (false)
{
}

JsonValue::~JsonValue ()
{
}

bool JsonValue::getSuccessFullyLoaded () const
{
    return (m_successFullyLoaded);
}

void JsonValue::setSuccessFullyLoaded (const bool &successFullyLoaded)
{
    m_successFullyLoaded = successFullyLoaded;
}

}
