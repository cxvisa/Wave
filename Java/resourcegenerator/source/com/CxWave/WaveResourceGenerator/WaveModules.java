/***************************************************************************
 *   Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc             *
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

public class WaveModules extends WaveResourceGeneratorElement
{
    private Vector<WaveModule> m_waveModules;
    private int                m_componentId;
    private int                m_nextModuleId;
    private String             m_packageName;
    private String             m_destinationPath;

    WaveModules ()
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_MODULES.getXmlTagName ());

        m_waveModules = new Vector<WaveModule> ();

        m_componentId  = 0;
        m_nextModuleId = 0;
    }

    public int getComponentId ()
    {
        return (m_componentId);
    }

    public void setComponentId (final int componentId)
    {
        m_componentId = componentId;
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

                if (elementTagName.equals(WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_MODULE.getXmlTagName ()))
                {
                    WaveModule waveModule = new WaveModule ();

                    waveModule.setPackageName     (m_packageName);
                    waveModule.setDestinationPath (m_destinationPath);
                    waveModule.setComponentId     (m_componentId);
                    waveModule.setModuleId        (m_nextModuleId);

                    m_nextModuleId++;

                    waveModule.setBaseDirectoryPath (getBaseDirectoryPath ());

                    waveModule.loadFromDomNode (childNode);

                    m_waveModules.add (waveModule);
                }
            }
        }
    }

    public void loadFromFile (final String waveModulesFilePath) throws ParserConfigurationException, SAXException, IOException
    {
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance ();
        DocumentBuilder        documentBuilder        = documentBuilderFactory.newDocumentBuilder ();

        //System.out.println ("        Using " + waveModulesFilePath + " for reading Wave Modules.");

        File waveModulesFile = new File (waveModulesFilePath);

        Document document = documentBuilder.parse (waveModulesFile);

        //System.out.println ("        Successfully obtained DOM Document.");

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

        //System.out.println ("        Node Name : " + nodeName);

        boolean matches = (getElementName ()).equals (nodeName);

        assert matches : "Loading from Dom Node where the node name does not match the expected value";

        loadFromDomNode (rootElement);
    }

    public void setDestinationPath (final String destinationPath)
    {
        m_destinationPath = destinationPath;
    }
}
