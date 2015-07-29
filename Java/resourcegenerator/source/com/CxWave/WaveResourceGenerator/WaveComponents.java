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

public class WaveComponents extends WaveResourceGeneratorElement
{
    private String                m_loadedFromFile;
    private Vector<WaveComponent> m_waveComponents;
    private int                   m_nextComponentId;
    private String                m_packageName;
    private String                m_destinationPath;

    public WaveComponents ()
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_WAVE_COMPONENTS.getXmlTagName ());

        m_waveComponents = new Vector<WaveComponent> ();

        m_nextComponentId = 0;
    }

    public String getPackageName ()
    {
        return (m_packageName);
    }

    public void setPackageName (final String packageName)
    {
        m_packageName = packageName;
    }

    public void loadFromFile (final String waveComponentsFilePath) throws ParserConfigurationException, SAXException, IOException
    {
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance ();
        DocumentBuilder        documentBuilder        = documentBuilderFactory.newDocumentBuilder ();

        //System.out.println ("Using " + waveComponentsFilePath + " for reading Wave Components.");

        File waveComponmentsFile = new File (waveComponentsFilePath);

        String waveComponmentsFileDirectory = waveComponmentsFile.getParent ();

        m_loadedFromFile      = waveComponentsFilePath;

        setBaseDirectoryPath (waveComponmentsFileDirectory);

        Document document = documentBuilder.parse(waveComponmentsFile);

        //System.out.println ("Successfully obtained DOM Document.");

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

        //System.out.println ("Node Name : " + nodeName);

        boolean matches = (getElementName ()).equals (nodeName);

        assert matches : "Loading from Dom Node where the node name does not match the expected value";

        loadFromDomNode (rootElement);
    }

    @Override
    public void loadFromDomNode (Node node)
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

                if (elementTagName.equals(WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_WAVE_COMPONENT.getXmlTagName ()))
                {
                    WaveComponent waveComponent = new WaveComponent ();

                    waveComponent.setPackageName     (m_packageName);
                    waveComponent.setDestinationPath (m_destinationPath);
                    waveComponent.setComponentId     (m_nextComponentId);

                    m_nextComponentId++;

                    waveComponent.setBaseDirectoryPath (getBaseDirectoryPath ());

                    waveComponent.loadFromDomNode (childNode);

                    m_waveComponents.add (waveComponent);
                }
            }
        }
    }

    public void setDestinationPath (final String destinationPath)
    {
                       m_destinationPath = destinationPath;
    }
}
