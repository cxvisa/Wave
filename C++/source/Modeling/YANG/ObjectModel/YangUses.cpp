/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangUses.h"

namespace WaveNs
{

YangUses::YangUses ()
    : YangElement (getYangName (), "")
{
}

YangUses::~YangUses()
{
}

string YangUses::getYangName ()
{
    return ("uses");
}

YangElement *YangUses::createInstance ()
{
    return (new YangUses ());
}

}
