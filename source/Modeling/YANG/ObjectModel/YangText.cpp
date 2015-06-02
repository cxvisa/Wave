/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangText.h"

namespace WaveNs
{

YangText::YangText ()
    : YangElement (getYangName (), "")
{
}

YangText::~YangText()
{
}

string YangText::getYangName ()
{
    return ("text");
}

YangElement *YangText::createInstance ()
{
    return (new YangText ());
}

void YangText::loadValue (const string &value)
{
    setValue (value);
}

}
