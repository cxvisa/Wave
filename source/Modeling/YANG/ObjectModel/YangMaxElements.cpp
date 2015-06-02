/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangMaxElements.h"

namespace WaveNs
{

YangMaxElements::YangMaxElements ()
    : YangElement (getYangName (), "")
{
}

YangMaxElements::~YangMaxElements()
{
}

string YangMaxElements::getYangName ()
{
    return ("max-elements");
}

YangElement *YangMaxElements::createInstance ()
{
    return (new YangMaxElements ());
}

}
