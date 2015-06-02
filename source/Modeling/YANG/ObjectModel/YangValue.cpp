/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangValue.h"

#include <stdlib.h>

namespace WaveNs
{

YangValue::YangValue ()
    : YangElement (getYangName (), ""),
      m_value     (0)
{
}

YangValue::~YangValue()
{
}

string YangValue::getYangName ()
{
    return ("value");
}

YangElement *YangValue::createInstance ()
{
    return (new YangValue ());
}

void YangValue::loadValue (const string &value)
{
    YangElement::setValue (value);
}


void YangValue::processAttribute (const string &attributeName, const string &attributeValue)
{
    if ("value" == attributeName)
    {
                     setName  (attributeName);
        YangElement::setValue (attributeValue);
                     setValue (strtoul (attributeValue.c_str (), NULL, 10));
    }
}

UI32 YangValue::getValue () const
{
    return (m_value);
}

void YangValue::setValue (const UI32 &value)
{
    m_value = value;
}

}
