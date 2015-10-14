/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Xml;

public class XmlFile
{
    private String m_xmlFilePath;

    public XmlFile (final String xmlFilePath)
    {
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
}
