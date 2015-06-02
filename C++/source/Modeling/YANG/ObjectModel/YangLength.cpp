/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangLength.h"

namespace WaveNs
{

YangLength::YangLength ()
    : YangElement (getYangName (), "")
{
}

YangLength::~YangLength()
{
}

string YangLength::getYangName ()
{
    return ("length");
}

YangElement *YangLength::createInstance ()
{
    return (new YangLength ());
}

}
