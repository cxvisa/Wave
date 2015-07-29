/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

import java.io.File;
import java.io.IOException;
import java.util.Vector;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class WaveModuleResources extends WaveResourceGeneratorElement
{
    private Vector<WaveResourceEnum> m_waveResourceEnums;
    private int                      m_componentId;
    private int                      m_moduleId;
    private int                      m_nextResourceEnumId;
    private String                   m_packageName;
    private String                   m_destinationPath;

    WaveModuleResources ()
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_MODULE_RESOURCES.getXmlTagName ());

        m_waveResourceEnums = new Vector<WaveResourceEnum> ();

        m_componentId        = 0;
        m_moduleId           = 0;
        m_nextResourceEnumId = 0;
    }

    public int getComponentId ()
    {
        return (m_componentId);
    }

    public void setComponentId (final int componentId)
    {
        m_componentId = componentId;
    }

    public int getModuleId ()
    {
        return (m_moduleId);
    }

    public void setModuleId (final int moduleId)
    {
        m_moduleId = moduleId;
    }

    public String getPackageName ()
    {
        return (m_packageName);
    }

    public void setPackageName (final String packageName)
    {
        m_packageName = packageName;
    }

    @Override
    void loadFromDomNode(Node node)
    {
        NodeList nodeList = node.getChildNodes ();

        int numberOfNodes = nodeList.getLength ();
        int i               = 0;

        for (i = 0; i < numberOfNodes; i++)
        {
            Node childNode = nodeList.item (i);

            if (Node.ELEMENT_NODE == (childNode.getNodeType()))
            {
                final Element element        = (Element) (childNode);
                final String  elementTagName = element.getTagName ();

                if (elementTagName.equals(WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_RESOURCE_ENUM.getXmlTagName ()))
                {
                    WaveResourceEnum waveResourceEnum = new WaveResourceEnum ();

                    waveResourceEnum.setPackageName     (m_packageName);
                    waveResourceEnum.setDestinationPath (m_destinationPath);
                    waveResourceEnum.setComponentId     (m_componentId);
                    waveResourceEnum.setModuleId        (m_moduleId);
                    waveResourceEnum.setResourceEnumId  (m_nextResourceEnumId);

                    waveResourceEnum.setBaseDirectoryPath (getBaseDirectoryPath ());

                    waveResourceEnum.loadFromDomNode (childNode);

                    m_nextResourceEnumId = waveResourceEnum.getNextResourceId ();

                    m_waveResourceEnums.add (waveResourceEnum);

                    waveResourceEnum.generateJavaEnumFile ();
                }
            }
        }
    }

    public void loadFromFile (final String waveModuleResourcesFilePath) throws ParserConfigurationException, SAXException, IOException
    {
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance ();
        DocumentBuilder        documentBuilder        = documentBuilderFactory.newDocumentBuilder ();

        //System.out.println ("            Using " + waveModuleResourcesFilePath + " for reading Wave Modules.");

        File waveModulesFile = new File (waveModuleResourcesFilePath);

        Document document = documentBuilder.parse (waveModulesFile);

        //System.out.println ("            Successfully obtained DOM Document.");

        if (null == document)
        {
            return;
        }

        Element rootElement = document.getDocumentElement ();

        if (null == rootElement)
        {
            return;
        }

        final String nodeName = rootElement.getNodeName ();

        //System.out.println ("            Node Name : " + nodeName);

        boolean matches = (getElementName ()).equals (nodeName);

        assert matches : "Loading from Dom Node where the node name does not match the expected value";

        loadFromDomNode (rootElement);
    }

    public void setDestinationPath (final String destinationPath)
    {
                          m_destinationPath = destinationPath;
    }
}
