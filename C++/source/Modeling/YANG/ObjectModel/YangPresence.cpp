/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangPresence.h"

namespace WaveNs
{

YangPresence::YangPresence ()
    : YangElement (getYangName (), "")
{
}

YangPresence::~YangPresence()
{
}

string YangPresence::getYangName ()
{
    return ("presence");
}

YangElement *YangPresence::createInstance ()
{
    return (new YangPresence ());
}

}
