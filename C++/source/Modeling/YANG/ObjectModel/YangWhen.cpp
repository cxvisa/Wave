/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangWhen.h"
#include "Modeling/YANG/ObjectModel/YangDisplayConfigurationContext.h"
#include "Modeling/XPath/WaveXPathExpressionElement.h"

namespace WaveNs
{

YangWhen::YangWhen ()
    : YangElement                   (getYangName (), ""),
      m_pWaveXPathExpressionElement (NULL)
{
}

YangWhen::~YangWhen()
{
    if (NULL != m_pWaveXPathExpressionElement)
    {
        delete m_pWaveXPathExpressionElement;
    }
}

string YangWhen::getYangName ()
{
    return ("when");
}

YangElement *YangWhen::createInstance ()
{
    return (new YangWhen ());
}

void YangWhen::setConditionString (const string &conditionString)
{
    prismAssert (false == conditionString.empty (), __FILE__, __LINE__);

    m_conditionString = conditionString;
}

string YangWhen::getConditionString () const
{
    return m_conditionString;
}

void YangWhen::processAttribute (const string &attributeName, const string &attributeValue)
{
    if ("condition" == attributeName)
    {
        setConditionString (attributeValue);

        // trace (TRACE_LEVEL_INFO, string ("YangWhen::processAttribute : conditionString [") + getConditionString () + string ("]"));

        m_pWaveXPathExpressionElement = WaveXPathExpressionElement::buildWaveXPathExpressionElementTree (getConditionString ());
        prismAssert (NULL != m_pWaveXPathExpressionElement, __FILE__, __LINE__);

        // m_pWaveXPathExpressionElement->debugPrint (0);
    }
}

bool YangWhen::evaluateCondition (YangDisplayConfigurationContext *pYangDisplayConfigurationContext)
{
    prismAssert (NULL != m_pWaveXPathExpressionElement, __FILE__, __LINE__);

    YangElement *pParentYangElement = getPParentElement ();
    prismAssert (NULL != pParentYangElement, __FILE__, __LINE__);

    // trace (TRACE_LEVEL_INFO, string ("YangWhen::evaluateCondition : conditionString [") + getConditionString () + string ("]"));

    WaveXPathExpressionValue resultValue = m_pWaveXPathExpressionElement->evaluateElement ((*pYangDisplayConfigurationContext), pParentYangElement);

    return resultValue.getBoolValue ();
}

}
