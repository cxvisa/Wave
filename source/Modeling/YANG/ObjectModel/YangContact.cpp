/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangContact.h"

namespace WaveNs
{

YangContact::YangContact ()
    : YangElement (getYangName (), "")
{
}

YangContact::~YangContact()
{
}

string YangContact::getYangName ()
{
    return ("contact");
}

YangElement *YangContact::createInstance ()
{
    return (new YangContact ());
}

}
