/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangMandatory.h"

namespace WaveNs
{

YangMandatory::YangMandatory ()
    : YangElement (getYangName (), "")
{
}

YangMandatory::~YangMandatory()
{
}

string YangMandatory::getYangName ()
{
    return ("mandatory");
}

YangElement *YangMandatory::createInstance ()
{
    return (new YangMandatory ());
}

}
