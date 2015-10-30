/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashMap;
import java.util.Map;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class ReflectionAttributesMap
{
    private final Map<UI32, ReflectionAttribute>   m_attributes;
    private final UI32                             m_nextAvailableAttributeTag;
    private final UI32                             m_nextAvailableAttributeTagForMapping;
    private final Map<String, ReflectionAttribute> m_attributesByName;
    private final Map<UI32, ReflectionAttribute>   m_attributesByUserTag;
    private final Map<UI32, String>                m_attributesOrderToNameMapping;

    public ReflectionAttributesMap ()
    {
        m_attributes = new HashMap<UI32, ReflectionAttribute> ();
        m_nextAvailableAttributeTag = new UI32 (0);
        m_nextAvailableAttributeTagForMapping = new UI32 (0);
        m_attributesByName = new HashMap<String, ReflectionAttribute> ();
        m_attributesByUserTag = new HashMap<UI32, ReflectionAttribute> ();
        m_attributesOrderToNameMapping = new HashMap<UI32, String> ();
    }

    public void addAttribute (final ReflectionAttribute reflectionAttribute)
    {
        WaveAssertUtils.waveAssert (null != reflectionAttribute);

        m_nextAvailableAttributeTag.increment ();

        final UI32 newAttributeTag = new UI32 (m_nextAvailableAttributeTag);

        reflectionAttribute.setAttributeTag (newAttributeTag);

        final boolean isAttributeTagAlreadyKnown = m_attributes.containsKey (newAttributeTag);

        if (false == isAttributeTagAlreadyKnown)
        {
            m_attributes.put (newAttributeTag, reflectionAttribute);

            final UI32 attributeUserTag = reflectionAttribute.getAttributeUserTag ();

            if (0 != (attributeUserTag.getValue ()))
            {
                if (!(isAKnownAttributeByUserTag (attributeUserTag)))
                {
                    m_attributesByUserTag.put (attributeUserTag, reflectionAttribute);
                }
                else
                {
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "ReflectionAttributesMap.addAttribute : Trying to add an Attribute with a User Tag that already exists : Attribute Name : %s, Tag : %u, User Tag : %u", reflectionAttribute.getAttributeName (), (reflectionAttribute.getAttributeTag ()).getValue (), (reflectionAttribute.getAttributeUserTag ()).getValue ());

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
                m_attributesByName.put (attributeName, reflectionAttribute);
            }
            else
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "ReflectionAttributesMap.addAttribute : Trying to add an Attribute with a name that already exists : Attribute Name : %s", reflectionAttribute.getAttributeName ());

                WaveAssertUtils.waveAssert ();
            }
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "ReflectionAttributesMap.addAttribute : Trying to add an Attribute with a Tag that already exists : Attribute Name : %s, Tag : %u", reflectionAttribute.getAttributeName (), (reflectionAttribute.getAttributeTag ()).getValue ());

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
}
