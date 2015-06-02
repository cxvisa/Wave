/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangFeature.h"

namespace WaveNs
{

YangFeature::YangFeature ()
    : YangElement (getYangName (), "")
{
}

YangFeature::~YangFeature()
{
}

string YangFeature::getYangName ()
{
    return ("feature");
}

YangElement *YangFeature::createInstance ()
{
    return (new YangFeature ());
}

}
