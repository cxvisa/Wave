/***************************************************************************
 *   Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

public class WaveModule extends WaveResourceGeneratorElement
{
    private String m_moduleName;
    private String m_filePath;
    private int    m_componentId;
    private int    m_moduleId;
    private String m_packageName;

    private WaveModuleResources m_waveModuleResources;
    private String              m_destinationPath;

    WaveModule ()
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_MODULE.getXmlTagName ());

        m_componentId = 0;
        m_moduleId    = 0;
    }

    public String getModuleName ()
    {
        return (m_moduleName);
    }

    public void setModuleName (final String moduleName)
    {
        m_moduleName = moduleName;
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
        String waveModuleName   = null;
        String waveModuleSource = null;

        NamedNodeMap attributesMap = node.getAttributes ();

        Node nameAttributeNode = attributesMap.getNamedItem ("Name");

        if (null != nameAttributeNode)
        {
            waveModuleName = nameAttributeNode.getNodeValue ();
        }

        Node sourceAttributeNode = attributesMap.getNamedItem ("Source");

        if (null != nameAttributeNode)
        {
            waveModuleSource = sourceAttributeNode.getNodeValue ();
        }

        System.out.println ("        Wave Module (" + waveModuleName + ", " + waveModuleSource + ")");

        setModuleName (waveModuleName);
        setFilePath   (waveModuleSource);

        m_waveModuleResources = new WaveModuleResources ();

        m_waveModuleResources.setComponentId     (m_componentId);
        m_waveModuleResources.setModuleId        (m_moduleId);
        m_waveModuleResources.setPackageName     (m_packageName);
        m_waveModuleResources.setDestinationPath (m_destinationPath);

        m_waveModuleResources.setBaseDirectoryPath (getBaseDirectoryPath ());

        try
        {
            String adjustedFilePath = m_filePath;

            if ('/' != (adjustedFilePath.charAt(0)))
            {
                adjustedFilePath = getBaseDirectoryPath () + "/" + adjustedFilePath;
            }

            m_waveModuleResources.loadFromFile (adjustedFilePath);
        }
        catch (Exception exception)
        {
            System.out.println ("            Processing failed : " + exception.toString ());

            exception.printStackTrace ();
        }
    }

    public void setDestinationPath (final String destinationPath)
    {
        m_destinationPath = destinationPath;
    }
}
