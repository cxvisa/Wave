/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashMap;
import java.util.Map;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributesMap
{
    private final Map<UI32, Attribute>   m_attributes;
    private final UI32                   m_nextAvailableAttributeTag;
    private final UI32                   m_nextAvailableAttributeTagForMapping;
    private final Map<String, Attribute> m_attributesByName;
    private final Map<UI32, Attribute>   m_attributesByUserTag;
    private final Map<UI32, String>      m_attributesOrderToNameMapping;
    private SerializableObject           m_serializableObject;

    public AttributesMap ()
    {
        m_attributes = new HashMap<UI32, Attribute> ();
        m_nextAvailableAttributeTag = new UI32 (0);
        m_nextAvailableAttributeTagForMapping = new UI32 (0);
        m_attributesByName = new HashMap<String, Attribute> ();
        m_attributesByUserTag = new HashMap<UI32, Attribute> ();
        m_attributesOrderToNameMapping = new HashMap<UI32, String> ();
    }

    public void addAttribute (final Attribute attribute)
    {
        WaveAssertUtils.waveAssert (null != attribute);

        final ReflectionAttribute reflectionAttribute = attribute.getReflectionAttribute ();

        WaveAssertUtils.waveAssert (null != reflectionAttribute);

        m_nextAvailableAttributeTag.increment ();

        final UI32 newAttributeTag = new UI32 (m_nextAvailableAttributeTag);

        final boolean isAttributeTagAlreadyKnown = m_attributes.containsKey (newAttributeTag);

        if (false == isAttributeTagAlreadyKnown)
        {
            m_attributes.put (newAttributeTag, attribute);

            final UI32 attributeUserTag = reflectionAttribute.getAttributeUserTag ();

            if (0 != (attributeUserTag.getValue ()))
            {
                if (!(isAKnownAttributeByUserTag (attributeUserTag)))
                {
                    m_attributesByUserTag.put (attributeUserTag, attribute);
                }
                else
                {
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributesMap.addAttribute : Trying to add an Attribute with a User Tag that already exists : Attribute Name : %s, Tag : %u, User Tag : %u", reflectionAttribute.getAttributeName (), (reflectionAttribute.getAttributeTag ()).getValue (), (reflectionAttribute.getAttributeUserTag ()).getValue ());

                    WaveAssertUtils.waveAssert ();
                }
            }

            final String attributeName = reflectionAttribute.getAttributeName ();

            if (WaveStringUtils.isBlank (attributeName))
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "We do not support Empty Names for attributes.");

                WaveAssertUtils.waveAssert ();
            }

            if (!(isAKnownAttributeByName (attributeName)))
            {
                m_attributesByName.put (attributeName, attribute);
            }
            else
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributesMap.addAttribute : Trying to add an Attribute with a name that already exists : Attribute Name : %s", reflectionAttribute.getAttributeName ());

                WaveAssertUtils.waveAssert ();
            }
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributesMap.addAttribute : Trying to add an Attribute with a Tag that already exists : Attribute Name : %s, Tag : %u", reflectionAttribute.getAttributeName (), (reflectionAttribute.getAttributeTag ()).getValue ());

            WaveAssertUtils.waveAssert ();
        }
    }

    public boolean isAKnownAttributeByUserTag (final UI32 attributeUserTag)
    {
        return (m_attributesByUserTag.containsKey (attributeUserTag));
    }

    public boolean isAKnownAttributeByName (final String attributeName)
    {
        return (m_attributesByName.containsKey (attributeName));
    }

    public void setSerializableObject (final SerializableObject serializableObject)
    {
        m_serializableObject = serializableObject;
    }

    public void loadFromWaveConfiguraitonFile (final String waveConfigurationFilePath)
    {
        WaveAssertUtils.waveAssert (null != m_serializableObject);

        final WaveConfigurationFile waveConfigurationFile = new WaveConfigurationFile (waveConfigurationFilePath);

        WaveAssertUtils.waveAssert (null != waveConfigurationFile);

        for (final Map.Entry<UI32, Attribute> entry : m_attributes.entrySet ())
        {
            final Attribute attribute = entry.getValue ();

            WaveAssertUtils.waveAssert (null != attribute);

            attribute.loadValueFromWaveConfigurationFile (waveConfigurationFile, m_serializableObject);
        }

    }
}
