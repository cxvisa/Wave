/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangDescription.h"

namespace WaveNs
{

YangDescription::YangDescription ()
    : YangElement (getYangName (), "")
{
}

YangDescription::~YangDescription()
{
}

string YangDescription::getYangName ()
{
    return ("description");
}

YangElement *YangDescription::createInstance ()
{
    return (new YangDescription ());
}

}
