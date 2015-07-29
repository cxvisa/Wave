/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

import org.w3c.dom.Node;

public abstract class WaveResourceGeneratorElement
{
    private String m_elementName;
    private String m_baseDirectoryPath;

    public WaveResourceGeneratorElement (final String elementName)
    {
        m_elementName = elementName;
    }

    public String getElementName ()
    {
        return (m_elementName);
    }

    public void setElementName (final String elementName)
    {
        m_elementName = elementName;
    }

    public String getBaseDirectoryPath ()
    {
        return (m_baseDirectoryPath);
    }

    public void setBaseDirectoryPath (final String baseDirectoryPath)
    {
        m_baseDirectoryPath = baseDirectoryPath;
    }

    abstract void loadFromDomNode (Node node);
}
