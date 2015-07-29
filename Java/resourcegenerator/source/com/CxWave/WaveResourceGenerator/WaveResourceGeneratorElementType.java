/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

public enum WaveResourceGeneratorElementType
{
    WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_WAVE_COMPONENTS  ("WaveComponents"),
    WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_WAVE_COMPONENT   ("Component"),
    WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_MODULES          ("Modules"),
    WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_MODULE           ("Module"),
    WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_MODULE_RESOURCES ("ModuleResources"),
    WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_RESOURCE_ENUM    ("ResourceEnum"),
    WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_RESOURCE         ("Resource");

    private String m_xmlTagName;

    WaveResourceGeneratorElementType (final String xmlTagName)
    {
        m_xmlTagName = xmlTagName;
    }

    public String getXmlTagName ()
    {
        return (m_xmlTagName);
    }
}
