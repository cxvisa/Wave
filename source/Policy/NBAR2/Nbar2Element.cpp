/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2Element.h"
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

Nbar2Element::Nbar2Element ()
{
}

Nbar2Element::~Nbar2Element ()
{
}

string Nbar2Element::getNodeName () const
{
    return (m_nodeName);
}

void Nbar2Element::setNodeName (const string &nodeName)
{
    m_nodeName = nodeName;
}

void Nbar2Element::loadFromDomElement (DOMElement *pDomElement)
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

            // FIXME : Sagar: Implement the following virtual funciton.
            //---addAttribute (pAttributeName, pAttributeValue);

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

                Nbar2Element *pNbar2Element = getNbar2ElementByName (string (pNodeName));

                if (NULL != pNbar2Element)
                {
                    pNbar2Element->loadFromDomElement (pChildDomElement);
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

void Nbar2Element::loadTextAttributeFromDomElement (const string &textAttributeName, DOMElement *pDomElement)
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

Nbar2Element *Nbar2Element::getNbar2ElementByName (const string &nbar2ElementName)
{
    return (getNbar2Element (nbar2ElementName));
}

Attribute *Nbar2Element::getTextAttributeByName (const string &textAttributeName)
{
    return (getTextAttribute (textAttributeName));
}

bool Nbar2Element::isAKnownTextAttribute (const string &textAttributeName) const
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

Attribute *Nbar2Element::getTextAttribute (const string &textAttributeName) const
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

void Nbar2Element::addTextAttribute (const string &textAttributeName, Attribute *pAttribute)
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

bool Nbar2Element::isAKnownNbar2Element (const string &nbar2ElementName) const
{
    map<string, Nbar2Element *>::const_iterator element    = m_nodeNbar2Elements.find (nbar2ElementName);
    map<string, Nbar2Element *>::const_iterator endElement = m_nodeNbar2Elements.end  ();

    if (endElement == element)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

Nbar2Element *Nbar2Element::getNbar2Element (const string &nbar2ElementName) const
{
    map<string, Nbar2Element *>::const_iterator element    = m_nodeNbar2Elements.find (nbar2ElementName);
    map<string, Nbar2Element *>::const_iterator endElement = m_nodeNbar2Elements.end  ();

    if (endElement == element)
    {
        return (NULL);
    }
    else
    {
        return (element->second);
    }
}

void Nbar2Element::addNbar2Element (const string &nbar2ElementName, Nbar2Element *pNbar2Element)
{
    prismAssert (NULL != pNbar2Element, __FILE__, __LINE__);

    bool isKnown = isAKnownNbar2Element (nbar2ElementName);

    if (false == isKnown)
    {
        m_nodeNbar2Elements[nbar2ElementName] = pNbar2Element;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

}

