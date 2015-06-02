/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangOrderedBy.h"

namespace WaveNs
{

YangOrderedBy::YangOrderedBy ()
    : YangElement (getYangName (), "")
{
}

YangOrderedBy::~YangOrderedBy()
{
}

string YangOrderedBy::getYangName ()
{
    return ("ordered-by");
}

YangElement *YangOrderedBy::createInstance ()
{
    return (new YangOrderedBy ());
}

}
