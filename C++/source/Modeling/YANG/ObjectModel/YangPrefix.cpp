/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangPrefix.h"

namespace WaveNs
{

YangPrefix::YangPrefix ()
    : YangElement (getYangName (), "")
{
}

YangPrefix::YangPrefix (const string &value)
    : YangElement (getYangName (), ""),
      m_value     (value)
{
}

YangPrefix::~YangPrefix()
{
}

string YangPrefix::getYangName ()
{
    return ("prefix");
}

YangElement *YangPrefix::createInstance ()
{
    return (new YangPrefix ());
}

string YangPrefix::getValue () const
{
    return (m_value);
}

void YangPrefix::setValue (const string &value)
{
    m_value = value;
}

}
