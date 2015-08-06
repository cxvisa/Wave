/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangCase.h"
#include "Modeling/YANG/ObjectModel/YangLeaf.h"

namespace WaveNs
{

YangCase::YangCase ()
    : YangElement (getYangName (), "")
{
}

YangCase::~YangCase()
{
}

string YangCase::getYangName ()
{
    return ("case");
}

YangElement *YangCase::createInstance ()
{
    return (new YangCase ());
}

void YangCase::computeCliTargetNodeNameForSelf ()
{
    setCliTargetNodeName ("");
}

void YangCase::computeIsConfigurationForSelf ()
{
    if (false == (getIsFirstDataElementInHierarchy ()))
    {
        if (false == (getIsConfigurationExplicitlySet ()))
        {
            YangElement *pParentElement = getPParentElement ();

            if (NULL != pParentElement)
            {
                setIsConfiguration (pParentElement->getIsConfiguration ());
            }
        }
    }
}

bool YangCase::isYangElementForData () const
{
    return true;
}

void YangCase::displayConfiguration2 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData)
{
    UI32 numberOfChildElementsForData = selectedChildElementsForData.size ();

    for (UI32 i = 0; i < numberOfChildElementsForData; i++)
    {
        YangElement *pYangElement = selectedChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        YangLeaf *pYangLeaf = dynamic_cast<YangLeaf *> (pYangElement);

        if (NULL != pYangLeaf)
        {
            pYangLeaf->displayConfigurtionForLeaf (pYangDisplayConfigurationContext, NULL);

            continue;
        }

        pYangElement->displayConfiguration1 (pYangDisplayConfigurationContext);
    }
}

void YangCase::displayConfiguration3 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData)
{
    trace (TRACE_LEVEL_ERROR, "YangCase::displayConfiguration3 : ConfigurationSegment is empty.");

    debugPrint ();
}

bool YangCase::considerForHFileForCLanguage () const
{
    return (true);
}

}
