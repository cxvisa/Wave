/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangInput.h"

namespace WaveNs
{

YangInput::YangInput ()
    : YangElement (getYangName (), "")
{
}

YangInput::~YangInput()
{
}

string YangInput::getYangName ()
{
    return ("input");
}

YangElement *YangInput::createInstance ()
{
    return (new YangInput ());
}

}
