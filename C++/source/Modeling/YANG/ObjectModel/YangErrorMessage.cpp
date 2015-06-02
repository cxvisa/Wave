/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangErrorMessage.h"

namespace WaveNs
{

YangErrorMessage::YangErrorMessage ()
    : YangElement (getYangName (), "")
{
}

YangErrorMessage::~YangErrorMessage()
{
}

string YangErrorMessage::getYangName ()
{
    return ("error-message");
}

YangElement *YangErrorMessage::createInstance ()
{
    return (new YangErrorMessage ());
}

}
