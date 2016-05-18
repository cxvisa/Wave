/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.reflect.Field;
import java.util.HashSet;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributeBooleanVector extends Attribute
{
    private static final Vector<Boolean> s_temp = null;

    @Override
    public Set<String> getSupportedDataTypes ()
    {
        final Set<String> supportedDataTypes = new HashSet<String> ();

        try
        {
            supportedDataTypes.add ((((getClass ()).getDeclaredField ("s_temp")).getGenericType ()).getTypeName ());
        }
        catch (NoSuchFieldException | SecurityException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributeBooleanVector.getSupportedDataTypes : Could not return supported data type.  Exception : " + e.toString ());
            WaveAssertUtils.waveAssert ();
        }

        return (supportedDataTypes);
    }

    public void loadValueFromPlainString (final Vector<Boolean> value, final SerializableObject serializableObject)
    {
        WaveAssertUtils.waveAssert (null != serializableObject);

        WaveAssertUtils.waveAssert (null != value);

        final Field reflectionField = m_reflectionAttribute.getField ();

        WaveAssertUtils.waveAssert (null != reflectionField);

        try
        {
            // WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AttributeStringVector.loadValueFromPlainString :
            // Attribute loading
            // for Field : %s, Class : %s, value : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass
            // ()).getName (), value);

            // @formatter:off
            /*
            Object object = reflectionField.get (serializableObject);

            if (null == object)
            {
                final Class<?> fieldType = reflectionField.getType ();

                WaveAssertUtils.waveAssert (null != fieldType);

                final Constructor<?>[] declaredConstructors = fieldType.getDeclaredConstructors ();
                Constructor<?> constructorWithZeroArguments = null;

                for (final Constructor<?> constructor : declaredConstructors)
                {
                    if (0 == (constructor.getGenericParameterTypes ()).length)
                    {
                        constructorWithZeroArguments = constructor;
                    }
                }

                if (null == constructorWithZeroArguments)
                {
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributeBooleanVector.loadValueFromPlainString : Could not find constructor with 0 arguments for Field Type : %s", fieldType.getName ());
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributeBooleanVector.loadValueFromPlainString :     Please declare a constructor with no arguments and retry.");

                    WaveAssertUtils.waveAssert ();
                }
                else
                {

                    try
                    {
                        constructorWithZeroArguments.setAccessible (true);

                        object = constructorWithZeroArguments.newInstance ();
                    }
                    catch (final InstantiationException | InvocationTargetException e)
                    {
                        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributeBooleanVector.loadValueFromPlainString:  Instantiating fieldType :%s failed.  Status : %s", fieldType.getName (), e.toString ());
                        WaveAssertUtils.waveAssert ();
                    }
                }
            }

            WaveAssertUtils.waveAssert (null != object);

            if (object instanceof Collection)
            {
                reflectionField.set (serializableObject, value);
            }
            else
            {
                WaveAssertUtils.waveAssert ();
            }
            */
            // @formatter:on

            reflectionField.set (serializableObject, value);
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AttributeBooleanVector.loadValueFromPlainString : Attribute loading failed for Field : %s, Class : %s, value : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), value, e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }

    @Override
    public void loadValueFromWaveConfigurationFile (final WaveConfigurationFile waveConfigurationFile, final SerializableObject serializableObject, final String xmlWaveXPathPrefix)
    {
        WaveAssertUtils.waveAssert (null != waveConfigurationFile);

        WaveAssertUtils.waveAssert (null != serializableObject);

        final String xmlWaveXPathValue = getXmlWaveXPath (xmlWaveXPathPrefix);

        if (WaveStringUtils.isNotBlank (xmlWaveXPathValue))
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AttributeBooleanVector.loadValueFromWaveConfigurationFile : Field : %s, Class : %s, xmlWaveXPathValue : %s", m_reflectionAttribute.getAttributeName (), serializableObject.getClass ().getName (), xmlWaveXPathValue);

            final Vector<String> configurationValues = waveConfigurationFile.getConfigurationValues (xmlWaveXPathValue);

            if (null != configurationValues)
            {
                final Vector<Boolean> value = new Vector<Boolean> ();

                for (final String configurationValue : configurationValues)
                {
                    if (WaveStringUtils.isNotBlank (configurationValue))
                    {
                        value.add (configurationValue.equalsIgnoreCase ("true") ? true : false);
                    }
                }

                loadValueFromPlainString (value, serializableObject);
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
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

        @SuppressWarnings ("unchecked")
        final Vector<Boolean> data = (Vector<Boolean>) object;

        WaveAssertUtils.waveAssert (null != data);

        for (final Boolean b : data)
        {
            value.append ("#");
            value.append (b.toString ());
        }
    }

    @Override
    public void fromWaveString (final SerializableObject thisSerializableObject, final String value)
    {
        final Object object = getValue (thisSerializableObject);

        if (null == object)
        {
            return;
        }

        @SuppressWarnings ("unchecked")
        final Vector<Boolean> data = (Vector<Boolean>) object;

        WaveAssertUtils.waveAssert (null != data);

        data.clear ();

        int firstIndex = 0;
        int nextIndex = 0;

        while (true)
        {
            firstIndex = nextIndex;
            nextIndex = value.indexOf ("#", firstIndex + 1);

            final String valueString;

            if (-1 != nextIndex)
            {
                valueString = value.substring (firstIndex + 1, nextIndex);
            }
            else
            {
                valueString = value.substring (firstIndex + 1);
                break;
            }

            WaveAssertUtils.waveAssert (null != valueString);

            data.add (Boolean.valueOf (valueString));
        }
    }
}
