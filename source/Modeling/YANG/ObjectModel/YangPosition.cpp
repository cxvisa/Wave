/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangPosition.h"

namespace WaveNs
{

YangPosition::YangPosition ()
    : YangElement (getYangName (), "")
{
}

YangPosition::~YangPosition()
{
}

string YangPosition::getYangName ()
{
    return ("position");
}

YangElement *YangPosition::createInstance ()
{
    return (new YangPosition ());
}

void YangPosition::processAttribute (const string &attributeName, const string &attributeValue)
{
    if ("value" == attributeName)
    {
                     setName    (attributeName);
        YangElement::setValue   (attributeValue);

                     setValue   (strtoul (attributeValue.c_str (), NULL, 10));
    }
}

UI32 YangPosition::getValue () const
{
    return (m_value);
}

void YangPosition::setValue (const UI32 &value)
{
    m_value = value;
}

}
