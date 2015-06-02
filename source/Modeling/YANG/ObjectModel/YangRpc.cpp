/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangRpc.h"

namespace WaveNs
{

YangRpc::YangRpc ()
    : YangElement (getYangName (), "")
{
}

YangRpc::~YangRpc()
{
}

string YangRpc::getYangName ()
{
    return ("rpc");
}

YangElement *YangRpc::createInstance ()
{
    return (new YangRpc ());
}

void YangRpc::getAllCliTargetNodeNamesForData (vector<string> &allCliTargetNodeNamesForData) const
{
}

void YangRpc::computeCliTargetNodeNameMapForData (map<string, vector<YangElement *> > &cliTargetNodeNameMapForData) const
{
}

void YangRpc::computeWillBeShownInConfigurationTree ()
{
}

bool YangRpc::considerForComputingUsageCountForGroupingsForProgrammingLanguages () const
{
    return (false);
}

bool YangRpc::considerForHFileForCLanguage () const
{
    return (true);
}

}
