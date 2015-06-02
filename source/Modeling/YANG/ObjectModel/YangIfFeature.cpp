/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangIfFeature.h"

namespace WaveNs
{

YangIfFeature::YangIfFeature ()
    : YangElement (getYangName (), "")
{
}

YangIfFeature::~YangIfFeature()
{
}

string YangIfFeature::getYangName ()
{
    return ("if-feature");
}

YangElement *YangIfFeature::createInstance ()
{
    return (new YangIfFeature ());
}

}
