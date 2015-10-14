/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Xml;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import org.w3c.dom.Attr;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

public class XmlElement
{
    private String              m_name;
    private String              m_value;
    private Vector<String>      m_attributes;
    private Map<String, String> m_attributeValues;
    private Vector<XmlElement>  m_childElements;

    private static final String s_extraPaddingWhiteSpace = "    ";

    private void construct ()
    {
        // @formatter:off

        m_name                = new String ();
        m_value               = new String ();
        m_attributes          = new Vector<String> ();
        m_attributeValues     = new HashMap<String, String> ();
        m_childElements       = new Vector<XmlElement> ();

        // @formatter:on
    }

    public XmlElement ()
    {
        construct ();
    }

    public void loadFromDomNode (final Node node)
    {
        if (Node.ELEMENT_NODE == node.getNodeType ())
        {
            final Element element = (Element) node;

            m_name = element.getTagName ();
        }

        NamedNodeMap attributesMap = node.getAttributes ();

        int numberOfNamedAttributes = attributesMap.getLength ();
        int i = 0;

        for (i = 0; i < numberOfNamedAttributes; i++)
        {
            final Attr attribute = (Attr) (attributesMap.item (i));

            m_attributes.add (attribute.getNodeName ());

            m_attributeValues.put (attribute.getNodeName (), attribute.getNodeValue ());
        }

        NodeList nodeList = node.getChildNodes ();

        int numberOfNodes = nodeList.getLength ();

        for (i = 0; i < numberOfNodes; i++)
        {
            Node childNode = nodeList.item (i);
            short childNodeType = childNode.getNodeType ();

            if (Node.ELEMENT_NODE == childNodeType)
            {
                final XmlElement xmlElement = new XmlElement ();

                xmlElement.loadFromDomNode (childNode);

                m_childElements.add (xmlElement);

            }
            else if (Node.TEXT_NODE == childNodeType)
            {
                m_value = childNode.getNodeValue ();
            }
        }
    }

    public String getName ()
    {
        return (m_name);
    }

    private void setName (final String name)
    {
        m_name = name;
    }

    public String getValue ()
    {
        return (m_value);
    }

    private void setValue (final String value)
    {
        m_value = value;
    }

    public Vector<String> getAttributes ()
    {
        return (m_attributes);
    }

    public String getAttributeValue (final String attributeName)
    {
        return (m_attributeValues.get (attributeName));
    }

    public Vector<XmlElement> getChildElements ()
    {
        return (m_childElements);
    }

    public void debugPrint (final String prefixWhiteSpace)
    {
        System.out.printf ("%s%s(", prefixWhiteSpace, m_name);

        final int numberOfAttributes = m_attributes.size ();

        int i = 0;

        for (i = 0; i < numberOfAttributes; i++)
        {
            final String attributeName = m_attributes.get (i);

            System.out.printf ("%s=%s", attributeName, m_attributeValues.get (attributeName));

            if (numberOfAttributes - 1 != i)
            {
                System.out.printf (", ");
            }
        }

        System.out.printf (")\n");

        if (WaveStringUtils.isNotBlank (m_value))
        {
            System.out.printf ("%s%s%s\n", prefixWhiteSpace, s_extraPaddingWhiteSpace, m_value);
        }

        final int numberOfChildElements = m_childElements.size ();

        for (i = 0; i < numberOfChildElements; i++)
        {
            (m_childElements.get (i)).debugPrint (prefixWhiteSpace + s_extraPaddingWhiteSpace);
        }
    }
}
