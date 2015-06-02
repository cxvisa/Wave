/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangChoice.h"
#include "Modeling/YANG/ObjectModel/YangCase.h"
#include "Modeling/YANG/ObjectModel/YangDisplayConfigurationContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

YangChoice::YangChoice ()
    : YangElement (getYangName (), "")
{
}

YangChoice::~YangChoice()
{
}

string YangChoice::getYangName ()
{
    return ("choice");
}

YangElement *YangChoice::createInstance ()
{
    return (new YangChoice ());
}

void YangChoice::computeCliTargetNodeNameForSelf ()
{
    setCliTargetNodeName ("");
}

void YangChoice::computeIsConfigurationForSelf ()
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

bool YangChoice::isYangElementForData () const
{
    return true;
}

void YangChoice::displayConfiguration2 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData)
{
    ConfigurationSegmentInformation *pConfigurationSegmentInformation = getPConfigurationSegmentInformation ();

    if (NULL == pConfigurationSegmentInformation)
    {
        trace (TRACE_LEVEL_ERROR, string ("YangElement::displayConfiguration3 : [") + getName () + string ("], configurationSegment [") + getConfigurationSegmentName () + string ("] : does not know about managed object."));
        return;
    }

    WaveManagedObject *pWaveManagedObject = NULL;

    bool disableFilters = false;
    pYangDisplayConfigurationContext->getPWaveManagedObject (this, pWaveManagedObject, disableFilters);

    if (NULL == pWaveManagedObject)
    {
        return;
    }

    UI32 tagValue = getUserTagValue ();

    if (0 == tagValue)
    {
        trace (TRACE_LEVEL_ERROR, string ("YangChoice::displayConfiguration2 : tagValue = 0. name [") + getName () + string ("]"));

        return;
    }

    UI32 caseTag = pWaveManagedObject->getCase (tagValue);

    if (0 == caseTag)
    {
        trace (TRACE_LEVEL_DEBUG, string ("YangChoice::displayConfiguration2 : caseTag = 0. Choice name [") + getName () + string ("]"));

        return;
    }

    const vector<YangElement *> &pChildElementsForData = getPChildElementsForData ();

    UI32 numberOfChildElementsForData = pChildElementsForData.size ();

    for (UI32 i = 0; i < numberOfChildElementsForData; i++)
    {
        YangElement *pYangElement = pChildElementsForData[i];
        prismAssert (NULL != pYangElement, __FILE__, __LINE__);

        YangCase *pYangCase = dynamic_cast<YangCase *> (pYangElement);

        if (NULL == pYangCase)
        {
            continue;
        }

        if (caseTag != pYangCase->getUserTagValue ())
        {
            continue;
        }

        // pYangCase->displayConfiguration1 (pYangDisplayConfigurationContext, selectedChildElementsForData);
        pYangCase->displayConfiguration1 (pYangDisplayConfigurationContext);
    }
}

void YangChoice::displayConfiguration3 (YangDisplayConfigurationContext *pYangDisplayConfigurationContext, vector<YangElement *> &selectedChildElementsForData)
{
    trace (TRACE_LEVEL_ERROR, "YangChoice::displayConfiguration3 : ConfigurationSegment is empty.");
}

bool YangChoice::considerForHFileForCLanguage () const
{
    return (true);
}

}
