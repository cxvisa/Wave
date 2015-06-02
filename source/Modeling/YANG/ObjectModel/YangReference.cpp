/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangReference.h"

namespace WaveNs
{

YangReference::YangReference ()
    : YangElement (getYangName (), "")
{
}

YangReference::~YangReference()
{
}

string YangReference::getYangName ()
{
    return ("reference");
}

YangElement *YangReference::createInstance ()
{
    return (new YangReference ());
}

}
