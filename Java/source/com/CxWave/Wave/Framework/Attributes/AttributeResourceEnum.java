/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.reflect.Field;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.Repository.WaveResourcesRepository;
import com.CxWave.Wave.Resources.ResourceEnum.WaveResourceEnumInterface;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributeResourceEnum extends Attribute
{
    @Override
    public Set<String> getSupportedDataTypes ()
    {
        return (WaveJavaSourceRepository.getAllDescendantEnumsTypeNamesForInterface (WaveResourceEnumInterface.class.getName ()));
    }

    @Override
    public void loadValueFromPlainString (final String value, final SerializableObject serializableObject)
    {
        WaveAssertUtils.waveAssert (null != serializableObject);

        WaveAssertUtils.waveAssert (null != value);

        final Field reflectionField = m_reflectionAttribute.getField ();

        WaveAssertUtils.waveAssert (null != reflectionField);

        try
        {
            // WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Attribute.loadValueFromPlainString : Attribute loading
            // for Field : %s, Class : %s, value : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass
            // ()).getName (), value);

            final WaveResourceEnumInterface waveResourceEnumInterface = (WaveResourcesRepository.getInstance ()).getWaveResourceEnumInterfaceByResourceIdName (value);

            reflectionField.set (serializableObject, waveResourceEnumInterface);
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Attribute.loadValueFromPlainString : Attribute loading failed for Field : %s, Class : %s, value : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), value, e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }

    @Override
    public String toPlainString (final SerializableObject serializableObject)
    {
        return (super.toPlainString (serializableObject));
    }

    @Override
    public void toWaveString (final SerializableObject thisSerializableObject, final StringBuffer value)
    {
        final String valueString = toPlainString (thisSerializableObject);

        value.append (valueString);
    }

    @Override
    public void fromWaveString (final SerializableObject thisSerializableObject, final String value)
    {
        loadValueFromPlainString (value, thisSerializableObject);
    }
}
