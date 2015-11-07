/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Xml;

import java.io.File;
import java.io.IOException;
import java.util.Vector;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.xml.sax.SAXException;

import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;

public class XmlFile
{
    private String         m_xmlFilePath;
    private XmlRootElement m_xmlRootElement;

    private void construct ()
    {
        m_xmlFilePath = null;
        m_xmlRootElement = new XmlRootElement ();
    }

    public XmlFile (final String xmlFilePath)
    {
        construct ();

        m_xmlFilePath = xmlFilePath;

        load ();
    }

    public String getXmlFilePath ()
    {
        return (m_xmlFilePath);
    }

    public void setXmlFilePath (final String xmlFilePath)
    {
        m_xmlFilePath = xmlFilePath;

        reload ();
    }

    private void load ()
    {
        if (WaveStringUtils.isBlank (m_xmlFilePath))
        {
            return;
        }
        else
        {
            try
            {
                loadFromFile (m_xmlFilePath);
            }
            catch (ParserConfigurationException | SAXException | IOException e)
            {
                // TODO Auto-generated catch block
                System.out.printf ("%s\n", e.getMessage ());
                e.printStackTrace ();
            }
        }
    }

    public void reload ()
    {
        load ();
    }

    public void read (final String xmlFilePath)
    {
        setXmlFilePath (xmlFilePath);
    }

    public void write (final String xmlFilePath)
    {
    }

    public void loadFromFile (final String waveXmlFilePath) throws ParserConfigurationException, SAXException, IOException
    {
        final DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance ();
        final DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder ();

        System.out.println ("Using " + waveXmlFilePath + " for reading XML Content.");

        final File waveXmlFile = new File (waveXmlFilePath);

        final Document document = documentBuilder.parse (waveXmlFile);

        // System.out.println ("Successfully obtained DOM Document.");

        if (null == document)
        {
            return;
        }

        final Element rootElement = document.getDocumentElement ();

        if (null == rootElement)
        {
            return;
        }

        loadFromDomNode (rootElement);
    }

    private void loadFromDomNode (final Node node)
    {
        m_xmlRootElement.loadFromDomNode (node);
    }

    public void debugPrint ()
    {
        m_xmlRootElement.debugPrint ("");
    }

    public Vector<String> getTextNodeValuesByWaveXmlXPath (final String waveXmlXPath)
    {
        return (m_xmlRootElement.getTextNodeValuesByWaveXmlXPath (waveXmlXPath));
    }
}
