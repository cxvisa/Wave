/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangRange.h"

namespace WaveNs
{

YangRange::YangRange ()
    : YangElement (getYangName (), "")
{
}

YangRange::~YangRange()
{
}

string YangRange::getYangName ()
{
    return ("range");
}

YangElement *YangRange::createInstance ()
{
    return (new YangRange ());
}

}
