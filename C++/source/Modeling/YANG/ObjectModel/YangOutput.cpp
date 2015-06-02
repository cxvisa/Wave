/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangOutput.h"

namespace WaveNs
{

YangOutput::YangOutput ()
    : YangElement (getYangName (), "")
{
}

YangOutput::~YangOutput()
{
}

string YangOutput::getYangName ()
{
    return ("output");
}

YangElement *YangOutput::createInstance ()
{
    return (new YangOutput ());
}

bool YangOutput::considerForComputingUsageCountForGroupingsForProgrammingLanguages () const
{
    return (true);
}

}
