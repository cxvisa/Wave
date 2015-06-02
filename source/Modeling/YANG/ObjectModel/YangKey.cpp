/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangKey.h"

namespace WaveNs
{

YangKey::YangKey ()
    : YangElement (getYangName (), "")
{
}

YangKey::~YangKey()
{
}

string YangKey::getYangName ()
{
    return ("key");
}

YangElement *YangKey::createInstance ()
{
    return (new YangKey ());
}

}
