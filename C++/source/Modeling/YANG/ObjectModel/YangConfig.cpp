/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangConfig.h"

namespace WaveNs
{

YangConfig::YangConfig ()
    : YangElement (getYangName (), "")
{
}

YangConfig::~YangConfig()
{
}

string YangConfig::getYangName ()
{
    return ("config");
}

YangElement *YangConfig::createInstance ()
{
    return (new YangConfig ());
}

void YangConfig::updateParentAnnotations ()
{   
//    WaveNs::trace (TRACE_LEVEL_INFO, "Yangconfig:: updateParentAnnotationBitMap-------------------------------------- "  );

    string configValue;
    getAttributeValue ("value", configValue);
    waveAssert ("" != configValue, __FILE__, __LINE__);

    if ("false" == configValue)
    {
        (getPParentElement())->setIsConfiguration (false);
    }
    else
    {
        (getPParentElement())->setIsConfiguration (true);
    }

    (getPParentElement())->setIsConfigurationExplicitlySet (true);
}

}
