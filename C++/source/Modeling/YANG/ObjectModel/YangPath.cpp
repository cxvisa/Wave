/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangPath.h"

namespace WaveNs
{

YangPath::YangPath ()
    : YangElement (getYangName (), "")
{
}

YangPath::~YangPath()
{
}

string YangPath::getYangName ()
{
    return ("path");
}

YangElement *YangPath::createInstance ()
{
    return (new YangPath ());
}

}
