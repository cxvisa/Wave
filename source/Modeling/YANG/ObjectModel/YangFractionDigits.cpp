/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangFractionDigits.h"

namespace WaveNs
{

YangFractionDigits::YangFractionDigits ()
    : YangElement (getYangName (), "")
{
}

YangFractionDigits::~YangFractionDigits()
{
}

string YangFractionDigits::getYangName ()
{
    return ("fraction-digits");
}

YangElement *YangFractionDigits::createInstance ()
{
    return (new YangFractionDigits ());
}

}
