/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Types/Number.h"
#include "Framework/Utils/AssertUtils.h"

#include <errno.h>

namespace WaveNs
{

Number::Number ()
    : m_ld (0.0L)
{
}

Number::Number (const string &numberInStringFormat)
    : m_ld (0)
{
    fromString (numberInStringFormat);
}

Number::Number (const LD &ld)
    : m_ld (ld)
{
}

Number::Number (const Number &number)
{
    m_ld = number.m_ld;
}

Number::~Number ()
{
}

bool Number::isAValidNumber (const string &numberInStringFormat)
{
    char *pEndPtr = NULL;

    errno = 0;

    strtold (numberInStringFormat.c_str (), &pEndPtr);

    if (0 == errno)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

string Number::toString () const
{
    string  tempString;
    char   *pTempPtr    = new char[512];

    prismAssert (NULL != pTempPtr, __FILE__, __LINE__);

    snprintf (pTempPtr, 512, "%Lf", m_ld);

    tempString = pTempPtr;

    return (tempString);
}

void Number::fromString (const string &numberInStringFormat)
{
    char *pEndPtr = NULL;

    errno = 0;

    LD temp = strtold (numberInStringFormat.c_str (), &pEndPtr);

    if (0 == errno)
    {
        m_ld = temp;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

LD Number::getLd () const
{
    return (m_ld);
}

void Number::setLd (const LD &ld)
{
    m_ld = ld;
}

Number &Number::operator = (const Number &number)
{
    m_ld = number.m_ld;

    return (*this);
}

bool Number::operator == (const Number &number)
{
    return (m_ld == number.m_ld);
}

bool Number::operator != (const Number &number)
{
    return (m_ld != number.m_ld);
}

bool Number::operator > (const Number &number)
{
    return (m_ld > number.m_ld);
}

bool Number::operator >= (const Number &number)
{
    return (m_ld >= number.m_ld);
}

bool Number::operator < (const Number &number)
{
    return (m_ld < number.m_ld);
}

bool Number::operator <= (const Number &number)
{
    return (m_ld <= number.m_ld);
}

}
