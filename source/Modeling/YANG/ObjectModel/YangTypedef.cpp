/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangTypedef.h"

namespace WaveNs
{

YangTypedef::YangTypedef ()
    : YangElement (getYangName (), "")
{
}

YangTypedef::YangTypedef (const string &name)
    : YangElement (getYangName (), name)
{
}

YangTypedef::~YangTypedef()
{
}

string YangTypedef::getYangName ()
{
    return ("typedef");
}

YangElement *YangTypedef::createInstance ()
{
    return (new YangTypedef ());
}

}
