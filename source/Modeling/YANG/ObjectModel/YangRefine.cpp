/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangRefine.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

YangRefine::YangRefine ()
    : YangElement (getYangName (), "")
{
}

YangRefine::~YangRefine()
{
}

string YangRefine::getYangName ()
{
    return ("refine");
}

YangElement *YangRefine::createInstance ()
{
    return (new YangRefine ());
}

void YangRefine::processAttribute (const string &attributeName, const string &attributeValue)
{
    if ("target-node" == attributeName)
    {
        setTargetExpression (attributeValue);
    }
}

string YangRefine::getTargetExpression () const
{
    return m_targetExpression;
}

void YangRefine::setTargetExpression (const string &targetExpression)
{
    m_targetExpression = targetExpression;
}

void YangRefine::refineYangElements (vector<YangElement *> &childElementsInGrouping)
{
    vector<string> tokens;
    StringUtils::tokenize (m_targetExpression, tokens, '/');
    UI32 numberOfTokens = tokens.size ();

    if (0 == numberOfTokens)
    {
        return;
    }

    string targetName;
    string targetRootName;

    targetRootName = tokens[0];

    for (UI32 i = 1; i < numberOfTokens; i++)
    {
        if (1 != i)
        {
            targetName += "/";
        }

        targetName += tokens[i];
    }

    UI32 numberOfChildElementsInGrouping = childElementsInGrouping.size ();

    for (UI32 i = 0; i < numberOfChildElementsInGrouping; i++)
    {
        YangElement *pYangElementToBeRefined = childElementsInGrouping[i];
        prismAssert (NULL != pYangElementToBeRefined, __FILE__, __LINE__);

        if (targetRootName != pYangElementToBeRefined->getName ())
        {
            continue;
        }

        YangElement *pTargetYangElement = pYangElementToBeRefined->getYangElementForTargetNode (targetName);

        if (NULL != pTargetYangElement)
        {
            trace (TRACE_LEVEL_INFO, string ("YangRefine::refineYangElements : refining [") + m_targetExpression + string ("]"));
            refineYangElement (pTargetYangElement);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, string ("YangRefine::refineYangElements : For [") + targetName + string ("], pTargetYangElement is NULL."));
        }
    }
}

}
