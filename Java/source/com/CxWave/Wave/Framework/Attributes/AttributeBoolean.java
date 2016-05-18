/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.reflect.Field;
import java.util.HashSet;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributeBoolean extends Attribute
{

    @Override
    public Set<String> getSupportedDataTypes ()
    {
        final Set<String> supportedDataTypes = new HashSet<String> ();

        supportedDataTypes.add (boolean.class.getTypeName ());
        supportedDataTypes.add (Boolean.class.getTypeName ());

        return (supportedDataTypes);
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
            reflectionField.set (serializableObject, value.equalsIgnoreCase ("true") ? true : false);
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributeBoolean.loadValueFromPlainString : Attribute loading failed for Attribute : %s, Class : %s, value : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), value, e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }

    @Override
    public void toWaveString (final SerializableObject thisSerializableObject, final StringBuffer value)
    {
        final Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            return;
        }

        final Boolean data = (Boolean) object;

        WaveAssertUtils.waveAssert (null != data);

        value.append (data ? "true" : "false");
    }

    @Override
    public void fromWaveString (final SerializableObject thisSerializableObject, final String value)
    {
        final Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            return;
        }

        Boolean data = (Boolean) object;

        final String valueString = value;

        if ((valueString.equalsIgnoreCase ("true")) || (valueString.equalsIgnoreCase ("t")))
        {
            data = true;
        }
        else
        {
            data = false;
        }
    }
}
