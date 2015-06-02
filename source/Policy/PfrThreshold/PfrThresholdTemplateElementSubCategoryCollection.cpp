/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PfrThreshold/PfrThresholdTemplateElementSubCategoryCollection.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

PfrThresholdTemplateElementSubCategoryCollection::PfrThresholdTemplateElementSubCategoryCollection ()
    : PfrThresholdElement ()
{
}

PfrThresholdTemplateElementSubCategoryCollection::~PfrThresholdTemplateElementSubCategoryCollection ()
{
}

void PfrThresholdTemplateElementSubCategoryCollection::loadTextAttributeFromDomElement (const string &textAttributeName, DOMElement *pDomElement)
{
    if ("SubCategoryName" == textAttributeName)
    {
        string           subCategoryName;
        AttributeString *pAttributeString = new AttributeString (&subCategoryName);

        prismAssert (NULL != pAttributeString, __FILE__, __LINE__);

        char    *pNodeValue = NULL;
        DOMNode *pDomNode   = pDomElement->getFirstChild ();

        prismAssert (NULL != pDomNode, __FILE__, __LINE__);

        pNodeValue = XMLString::transcode (pDomNode->getNodeValue ());

        //cout << "(" << pNodeValue << ")" << endl;

        pAttributeString->loadFromPlainString (pNodeValue);

        m_subCategoryNames.push_back (subCategoryName);

        XMLString::release (&pNodeValue);
    }
    else
    {
        PfrThresholdElement::loadTextAttributeFromDomElement (textAttributeName, pDomElement);
    }
}

vector<string> &PfrThresholdTemplateElementSubCategoryCollection::getSubCategoryNames ()
{
    return (m_subCategoryNames);
}

}
