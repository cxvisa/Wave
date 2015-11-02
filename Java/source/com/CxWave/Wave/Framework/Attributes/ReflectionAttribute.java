/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.reflect.Field;

import com.CxWave.Wave.Framework.Type.UI32;

public class ReflectionAttribute
{
    private AttributeType m_attributeType;
    private String        m_AttributeName;
    private String        m_attributeFieldName;
    private UI32          m_attributeTag;
    private UI32          m_attributeUserTag;
    private boolean       m_isPrimary;
    private boolean       m_isOperational;
    private String        m_xmlWaveXPath;
    private Field         m_field;

    public ReflectionAttribute ()
    {
        m_attributeType = null;
        m_AttributeName = null;
        m_attributeTag = null;
        m_attributeUserTag = null;
        m_isPrimary = false;
        m_isOperational = false;
        m_xmlWaveXPath = null;

        m_field = null;
    }

    public ReflectionAttribute (final AttributeType attributeType, final String attributeName, final UI32 attributeUserTag, final boolean isPrimary, final boolean isOperational)
    {
        m_attributeType = attributeType;
        m_AttributeName = attributeName;
        m_attributeTag = null;
        m_attributeUserTag = attributeUserTag;
        m_isPrimary = isPrimary;
        m_isOperational = isOperational;
        m_xmlWaveXPath = null;
        m_field = null;
    }

    public ReflectionAttribute (final AttributeType attributeType, final String attributeName, final UI32 attributeUserTag)
    {
        m_attributeType = attributeType;
        m_AttributeName = attributeName;
        m_attributeTag = null;
        m_attributeUserTag = attributeUserTag;
        m_isPrimary = false;
        m_isOperational = false;
        m_xmlWaveXPath = null;
        m_field = null;
    }

    public ReflectionAttribute (final AttributeType attributeType, final String attributeName)
    {
        m_attributeType = attributeType;
        m_AttributeName = attributeName;
        m_attributeTag = new UI32 (0);
        m_attributeUserTag = new UI32 (0);
        m_isPrimary = false;
        m_isOperational = false;
        m_xmlWaveXPath = null;
        m_field = null;
    }

    public AttributeType getAttributeType ()
    {
        return m_attributeType;
    }

    public void setAttributeType (final AttributeType attributeType)
    {
        m_attributeType = attributeType;
    }

    public String getAttributeName ()
    {
        return m_AttributeName;
    }

    public void setAttributeName (final String attributeName)
    {
        m_AttributeName = attributeName;
    }

    public String getAttributeFieldName ()
    {
        return m_attributeFieldName;
    }

    public void setAttributeFieldName (final String attributeFieldName)
    {
        m_attributeFieldName = attributeFieldName;
    }

    public UI32 getAttributeTag ()
    {
        return m_attributeTag;
    }

    public void setAttributeTag (final UI32 attributeTag)
    {
        m_attributeTag = attributeTag;
    }

    public UI32 getAttributeUserTag ()
    {
        return m_attributeUserTag;
    }

    public void setAttributeUserTag (final UI32 attributeUserTag)
    {
        m_attributeUserTag = attributeUserTag;
    }

    public boolean getIsPrimary ()
    {
        return m_isPrimary;
    }

    public void setIsPrimary (final boolean isPrimary)
    {
        m_isPrimary = isPrimary;
    }

    public boolean getIsOperational ()
    {
        return m_isOperational;
    }

    public void setIsOperational (final boolean isOperational)
    {
        m_isOperational = isOperational;
    }

    public String getXmlWaveXPath ()
    {
        return m_xmlWaveXPath;
    }

    public void setXmlWaveXPath (final String xmlWaveXPath)
    {
        m_xmlWaveXPath = xmlWaveXPath;
    }

    public Field getField ()
    {
        return m_field;
    }

    public void setField (final Field field)
    {
        m_field = field;
    }
}
