/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangOrganization.h"

namespace WaveNs
{

YangOrganization::YangOrganization ()
    : YangElement (getYangName (), "")
{
}

YangOrganization::~YangOrganization()
{
}

string YangOrganization::getYangName ()
{
    return ("organization");
}

YangElement *YangOrganization::createInstance ()
{
    return (new YangOrganization ());
}

}
