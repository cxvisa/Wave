/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangDefault.h"

namespace WaveNs
{

YangDefault::YangDefault ()
    : YangElement (getYangName (), "")
{
}

YangDefault::~YangDefault()
{
}

string YangDefault::getYangName ()
{
    return ("default");
}

YangElement *YangDefault::createInstance ()
{
    return (new YangDefault ());
}

}
