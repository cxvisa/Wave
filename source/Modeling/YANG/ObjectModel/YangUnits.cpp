/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangUnits.h"

namespace WaveNs
{

YangUnits::YangUnits ()
    : YangElement (getYangName (), "")
{
}

YangUnits::~YangUnits()
{
}

string YangUnits::getYangName ()
{
    return ("units");
}

YangElement *YangUnits::createInstance ()
{
    return (new YangUnits ());
}

}
