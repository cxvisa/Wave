/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Serialization;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import com.CxWave.Wave.Framework.Attributes.AttributesMap;
import com.CxWave.Wave.Framework.Attributes.ReflectionAttributesMap;
import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class SerializableObjectRepository
{
    private static SerializableObjectRepository         s_serializableObjectRepository  = new SerializableObjectRepository ();

    private static Set<String>                          s_serializableClassesConsidered = new HashSet<String> ();

    private static Map<String, ReflectionAttributesMap> s_reflectionAttributesByClass   = new HashMap<String, ReflectionAttributesMap> ();

    private SerializableObjectRepository ()
    {
    }

    public static SerializableObjectRepository getInstance ()
    {
        if (null == s_serializableObjectRepository)
        {
            s_serializableObjectRepository = new SerializableObjectRepository ();
        }

        WaveAssertUtils.waveAssert (null != s_serializableObjectRepository);

        return (s_serializableObjectRepository);
    }

    public void initialize ()
    {
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "Initializing Serializable Object Repository ...");

        final Set<String> allSerializableObjects = WaveJavaSourceRepository.getAllDescendantsForClass (SerializableObject.class.getName ());

        for (final String serializableObject : allSerializableObjects)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, false, false, "    Considering %s ... ", serializableObject);

            final boolean isClassAnnotatedWithNonSerializable = WaveJavaSourceRepository.isClassAnnotatedWith (serializableObject, NonSerializable.class.getName ());

            if (!isClassAnnotatedWithNonSerializable)
            {
                s_serializableClassesConsidered.add (serializableObject);

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_SUCCESS, true, true, "Considered.");
            }
            else
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_WARN, true, true, "Ignored.");
            }
        }

        for (final String consideredSerializableObject : s_serializableClassesConsidered)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, false, false, "    Processing %s ... ", consideredSerializableObject);

            final AttributesMap attributesMap = WaveJavaSourceRepository.getAttributesMapForInheritanceHierarchyForClass (consideredSerializableObject);
        }
    }
}
