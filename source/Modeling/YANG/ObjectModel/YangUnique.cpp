/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kundan Sinha                                                 *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangUnique.h"

namespace WaveNs
{

YangUnique::YangUnique ()
    : YangElement (getYangName (), "")
{
}

YangUnique::~YangUnique()
{
}

string YangUnique::getYangName ()
{
    return ("unique");
}

YangElement *YangUnique::createInstance ()
{
    return (new YangUnique ());
}

}
