/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class WaveResource extends WaveResourceGeneratorElement
{
    private String m_waveResourceName;
    private String m_waveResourceValue;
    private int    m_componentId;
    private int    m_moduleId;
    private int    m_resourceEnumId;
    private int    m_resourceId;
    private int    m_effectiveResourceId;

    public WaveResource ()
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_RESOURCE.getXmlTagName ());

        m_componentId         = 0;
        m_moduleId            = 0;
        m_resourceEnumId      = 0;
        m_resourceId          = 0;
        m_effectiveResourceId = 0;
    }

    public String getWaveResourceName ()
    {
        return (m_waveResourceName);
    }

    public void setWaveResourceName (final String waveResourceName)
    {
        m_waveResourceName = waveResourceName;
    }

    public String getWaveResourceValue ()
    {
        return (m_waveResourceValue);
    }

    public void setWaveResourceValue (final String waveResourceValue)
    {
        m_waveResourceValue = waveResourceValue;
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

    public int getResourceEnumId ()
    {
        return (m_resourceEnumId);
    }

    public void setResourceEnumId (final int resourceEnumId)
    {
        m_resourceEnumId = resourceEnumId;
    }

    public int getResourceId ()
    {
        return (m_resourceId);
    }

    public void setResourceId (final int resourceId)
    {
        m_resourceId = resourceId;
    }

    public int getEffectiveResourceId ()
    {
        return (m_effectiveResourceId);
    }

    public void setEffectiveResourceId (final int effectiveResourceId)
    {
        m_effectiveResourceId = effectiveResourceId;
    }

    @Override
    void loadFromDomNode(Node node)
    {
        String waveResourceName   = null;

        NamedNodeMap attributesMap = node.getAttributes ();

        Node nameAttributeNode = attributesMap.getNamedItem ("Name");

        if (null != nameAttributeNode)
        {
            waveResourceName = nameAttributeNode.getNodeValue ();
        }

        setWaveResourceName (waveResourceName);

        m_effectiveResourceId = (m_componentId << 30) | (m_moduleId << 16) | (m_resourceId);

        System.out.format ("                Wave Resource (0x%08X, %s, ", m_effectiveResourceId, waveResourceName);

        NodeList nodeList = node.getChildNodes ();

        int numberOfNodes = nodeList.getLength ();
        int i               = 0;

        for (i = 0; i < numberOfNodes; i++)
        {
            Node childNode = nodeList.item (i);

            if (Node.TEXT_NODE == (childNode.getNodeType()))
            {
                setWaveResourceValue (childNode.getNodeValue ());

                System.out.print (getWaveResourceValue ());

                break;
            }
        }

        System.out.println (")");
    }
}
