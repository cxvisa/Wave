/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

public class WaveComponent extends WaveResourceGeneratorElement
{
    private String      m_componentName;
    private String      m_filePath;
    private WaveModules m_waveModules;
    private int         m_componentId;
    private String      m_packageName;
    private String      m_destinationPath;

    public WaveComponent ()
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_WAVE_COMPONENT.getXmlTagName ());

        m_componentName = null;
        m_filePath      = null;
    }

    public WaveComponent (final String componentName, final String filePath)
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_WAVE_COMPONENT.getXmlTagName ());

        m_componentName = componentName;
        m_filePath      = filePath;
    }

    public String getComponentName ()
    {
        return (m_componentName);
    }

    public void setComponentName (final String componentName)
    {
        m_componentName = componentName;
    }

    public String getFilePath ()
    {
        return (m_filePath);
    }

    public void setFilePath (final String filePath)
    {
        m_filePath = filePath;
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
    public void loadFromDomNode (Node node)
    {
        String waveComponentName   = null;
        String waveComponentSource = null;

        NamedNodeMap attributesMap = node.getAttributes ();

        Node nameAttributeNode = attributesMap.getNamedItem ("Name");

        if (null != nameAttributeNode)
        {
            waveComponentName = nameAttributeNode.getNodeValue ();
        }

        Node sourceAttributeNode = attributesMap.getNamedItem ("Source");

        if (null != nameAttributeNode)
        {
            waveComponentSource = sourceAttributeNode.getNodeValue ();
        }

        System.out.println ("    Wave Component (" + waveComponentName + ", " + waveComponentSource + ")");

        setComponentName (waveComponentName);
        setFilePath      (waveComponentSource);

        m_waveModules = new WaveModules ();

        m_waveModules.setComponentId     (m_componentId);
        m_waveModules.setPackageName     (m_packageName);
        m_waveModules.setDestinationPath (m_destinationPath);

        m_waveModules.setBaseDirectoryPath (getBaseDirectoryPath ());

        try
        {
            String adjustedFilePath = m_filePath;

            if ('/' != (adjustedFilePath.charAt(0)))
            {
                adjustedFilePath = getBaseDirectoryPath () + "/" + adjustedFilePath;
            }

            m_waveModules.loadFromFile (adjustedFilePath);
        }
        catch (Exception exception)
        {
            System.out.println ("        Processing failed : " + exception.toString ());

            exception.printStackTrace ();
        }
    }

    public void setDestinationPath (final String destinationPath)
    {
             m_destinationPath = destinationPath;
    }
}
