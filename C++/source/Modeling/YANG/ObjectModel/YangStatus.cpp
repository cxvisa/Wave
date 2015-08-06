/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangStatus.h"

namespace WaveNs
{

YangStatus::YangStatus ()
    : YangElement (getYangName (), "")
{
}

YangStatus::~YangStatus()
{
}

string YangStatus::getYangName ()
{
    return ("status");
}

YangElement *YangStatus::createInstance ()
{
    return (new YangStatus ());
}

void YangStatus::updateParentAnnotations ()
{   
    //WaveNs::trace (TRACE_LEVEL_INFO, "YangStatus:: updateParentAnnotationBitMap-------------------------------------- "  );
    string statusValue;

    getAttributeValue ("value", statusValue);
    waveAssert ("" != statusValue, __FILE__, __LINE__);

    if ("deprecated" == statusValue)
    {
        (getPParentElement())->setIsDeprecated (true);
    }

}

}
