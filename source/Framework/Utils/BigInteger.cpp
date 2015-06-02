/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/BigInteger.h"

namespace WaveNs
{

BigInteger::BigInteger (const SI64 &bigIntegerValue)
    : m_bigIntegerValue (bigIntegerValue)
{
}

BigInteger::~BigInteger ()
{
}

SI64 BigInteger::getIntegerValue () const
{
    return (m_bigIntegerValue);
}

void BigInteger::setIntegerValue (const SI64 &bigIntegerValue)
{
    m_bigIntegerValue = bigIntegerValue;
}

string BigInteger::toString () const
{
    char tempBuffer[256] = {0};

    snprintf (tempBuffer, 256, "%lld", m_bigIntegerValue);

    return (string (tempBuffer));
}

string BigInteger::toHexString () const
{
    char tempBuffer[256] = {0};

    snprintf (tempBuffer, 256, "%llX", m_bigIntegerValue);

    return (string (tempBuffer));
}

}
