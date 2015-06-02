/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/Integer.h"

namespace WaveNs
{

Integer::Integer (const SI32 &integerValue)
    : m_integerValue (integerValue)
{
}

Integer::~Integer ()
{
}

SI32 Integer::getIntegerValue () const
{
    return (m_integerValue);
}

void Integer::setIntegerValue (const SI32 &integerValue)
{
    m_integerValue = integerValue;
}

string Integer::toString () const
{
    char tempBuffer[32] = {0};

    snprintf (tempBuffer, 32, "%d", m_integerValue);

    return (string (tempBuffer));
}

string Integer::toHexString () const
{
    char tempBuffer[32] = {0};

    snprintf (tempBuffer, 32, "%X", m_integerValue);

    return (string (tempBuffer));
}

}
