/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PfrThreshold/PfrThresholdElement.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Attributes/Attributes.h"

 #include <xercesc/dom/DOM.hpp>
 #include <xercesc/framework/MemBufInputSource.hpp>
 #include <xercesc/framework/LocalFileInputSource.hpp>
 #include <xercesc/framework/StdOutFormatTarget.hpp>
 #include <xercesc/parsers/XercesDOMParser.hpp>
 #include <ctype.h>

 #include <iostream>
 #include <vector>
 #include <algorithm>

 using namespace XERCES_CPP_NAMESPACE;
 using namespace std;

namespace WaveNs
{

PfrThresholdElement::PfrThresholdElement ()
{
}

PfrThresholdElement::~PfrThresholdElement ()
{
}

string PfrThresholdElement::getNodeName () const
{
    return (m_nodeName);
}

void PfrThresholdElement::setNodeName (const string &nodeName)
{
    m_nodeName = nodeName;
}

void PfrThresholdElement::loadFromDomElement (DOMElement *pDomElement)
{

    char        *pNodeName         = NULL;
    char        *pAttributeName    = NULL;
    char        *pAttributeValue   = NULL;

    prismAssert (NULL != pDomElement, __FILE__, __LINE__);

    DOMElement  *pRootNode  = pDomElement;
    DOMNode     *pChildNode = NULL;

    pNodeName = XMLString::transcode (pRootNode->getNodeName ());

    if (NULL != pNodeName)
    {
        //cout << "\nNode Name : " << pNodeName << "\n";

        setNodeName (pNodeName);
    }

    XMLString::release (&pNodeName);

    DOMNamedNodeMap *pAttributesMap = pRootNode->getAttributes ();

    if (NULL != pAttributesMap)
    {
        UI32 numberOfAttributes = pAttributesMap->getLength ();
        UI32 i                  = 0;

        for (i = 0; i < numberOfAttributes; i++)
        {
            DOMNode *pAttributeDomNode = pAttributesMap->item (i);

            prismAssert (NULL != pAttributeDomNode, __FILE__, __LINE__);

            DOMAttr *pAttribute = dynamic_cast<DOMAttr *> (pAttributeDomNode);

            prismAssert (NULL != pAttribute, __FILE__, __LINE__);

            const XMLCh *pAttributeNameXmlChar  = pAttribute->getName  ();
            const XMLCh *pAttributeValueXmlChar = pAttribute->getValue ();

            prismAssert (NULL != pAttributeNameXmlChar,  __FILE__, __LINE__);
            prismAssert (NULL != pAttributeValueXmlChar, __FILE__, __LINE__);

            pAttributeName  = XMLString::transcode (pAttributeNameXmlChar);
            pAttributeValue = XMLString::transcode (pAttributeValueXmlChar);

            prismAssert (NULL != pAttributeName,  __FILE__, __LINE__);
            prismAssert (NULL != pAttributeValue, __FILE__, __LINE__);

            //cout << ">>>>>" << pAttributeName << "=" << pAttributeValue << "<<<<<\n";

            XMLString::release (&pAttributeName);
            XMLString::release (&pAttributeValue);
        }
    }

    string ignoreText = "#text";

    for (pChildNode = pRootNode->getFirstChild (); NULL != pChildNode; pChildNode = pChildNode->getNextSibling ())
    {
        DOMNode::NodeType nodeType = (DOMNode::NodeType) pChildNode->getNodeType ();

        if (DOMNode::ELEMENT_NODE == nodeType)
        {
            DOMElement  *pChildDomElement = dynamic_cast<DOMElement *> (pChildNode);

            prismAssert (NULL != pChildDomElement, __FILE__, __LINE__);

            pNodeName = XMLString::transcode (pChildNode->getNodeName ());

            if (NULL != pNodeName)
            {
                //---
                //cout << "    Child Node : " << pNodeName;

                PfrThresholdElement *pPfrThresholdElement = getPfrThresholdElementByName (string (pNodeName));

                if (NULL != pPfrThresholdElement)
                {
                    pPfrThresholdElement->loadFromDomElement (pChildDomElement);
                }
                else
                {
                    loadTextAttributeFromDomElement (pNodeName, pChildDomElement);
                }

                XMLString::release (&pNodeName);
            }
        }
        else if (DOMNode::TEXT_NODE == nodeType)
        {
            // Nothing for now
        }
    }
}

void PfrThresholdElement::loadTextAttributeFromDomElement (const string &textAttributeName, DOMElement *pDomElement)
{
    char      *pNodeValue = NULL;
    Attribute *pAttribute = getTextAttributeByName (textAttributeName);

    prismAssert (NULL != pAttribute, __FILE__, __LINE__);

    DOMNode *pDomNode = pDomElement->getFirstChild ();

    prismAssert (NULL != pDomNode, __FILE__, __LINE__);

    pNodeValue = XMLString::transcode (pDomNode->getNodeValue ());

    //cout << "(" << pNodeValue << ")" << endl;

    pAttribute->loadFromPlainString (pNodeValue);

    XMLString::release (&pNodeValue);
}

PfrThresholdElement *PfrThresholdElement::getPfrThresholdElementByName (const string &pfrThresholdElementName)
{
    return (getPfrThresholdElement (pfrThresholdElementName));
}

Attribute *PfrThresholdElement::getTextAttributeByName (const string &textAttributeName)
{
    return (getTextAttribute (textAttributeName));
}

bool PfrThresholdElement::isAKnownTextAttribute (const string &textAttributeName) const
{
    map<string, Attribute *>::const_iterator element    = m_nodeTextAttributes.find (textAttributeName);
    map<string, Attribute *>::const_iterator endElement = m_nodeTextAttributes.end  ();

    if (endElement == element)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

Attribute *PfrThresholdElement::getTextAttribute (const string &textAttributeName) const
{
    map<string, Attribute *>::const_iterator element    = m_nodeTextAttributes.find (textAttributeName);
    map<string, Attribute *>::const_iterator endElement = m_nodeTextAttributes.end  ();

    if (endElement == element)
    {
        return (NULL);
    }
    else
    {
        return (element->second);
    }
}

void PfrThresholdElement::addTextAttribute (const string &textAttributeName, Attribute *pAttribute)
{
    prismAssert (NULL != pAttribute, __FILE__, __LINE__);

    bool isKnown = isAKnownTextAttribute (textAttributeName);

    if (false == isKnown)
    {
        m_nodeTextAttributes[textAttributeName] = pAttribute;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

bool PfrThresholdElement::isAKnownPfrThresholdElement (const string &pfrThresholdElementName) const
{
    map<string, PfrThresholdElement *>::const_iterator element    = m_nodePfrThresholdElements.find (pfrThresholdElementName);
    map<string, PfrThresholdElement *>::const_iterator endElement = m_nodePfrThresholdElements.end  ();

    if (endElement == element)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

PfrThresholdElement *PfrThresholdElement::getPfrThresholdElement (const string &pfrThresholdElementName) const
{
    map<string, PfrThresholdElement *>::const_iterator element    = m_nodePfrThresholdElements.find (pfrThresholdElementName);
    map<string, PfrThresholdElement *>::const_iterator endElement = m_nodePfrThresholdElements.end  ();

    if (endElement == element)
    {
        return (NULL);
    }
    else
    {
        return (element->second);
    }
}

void PfrThresholdElement::addPfrThresholdElement (const string &pfrThresholdElementName, PfrThresholdElement *pPfrThresholdElement)
{
    prismAssert (NULL != pPfrThresholdElement, __FILE__, __LINE__);

    bool isKnown = isAKnownPfrThresholdElement (pfrThresholdElementName);

    if (false == isKnown)
    {
        m_nodePfrThresholdElements[pfrThresholdElementName] = pPfrThresholdElement;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

}

