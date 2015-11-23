/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.reflect.Field;
import java.util.HashSet;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AtributeLocationIdVector extends Attribute
{
    private static final Vector<LocationId> s_temp = null;

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
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AtributeLocationIdVector.getSupportedDataTypes : Could not return supported data type.  Exception : " + e.toString ());
            WaveAssertUtils.waveAssert ();
        }

        return (supportedDataTypes);
    }

    public void loadValueFromPlainString (final Vector<LocationId> value, final SerializableObject serializableObject)
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
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AtributeLocationIdVector.loadValueFromPlainString : Could not find constructor with 0 arguments for Field Type : %s", fieldType.getName ());
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AtributeLocationIdVector.loadValueFromPlainString :     Please declare a constructor with no arguments and retry.");

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
                        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AtributeLocationIdVector.loadValueFromPlainString:  Instantiating fieldType :%s failed.  Status : %s", fieldType.getName (), e.toString ());
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
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AtributeLocationIdVector.loadValueFromPlainString : Attribute loading failed for Field : %s, Class : %s, value : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), value, e.toString ());
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
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AtributeLocationIdVector.loadValueFromWaveConfigurationFile : Field : %s, Class : %s, xmlWaveXPathValue : %s", m_reflectionAttribute.getAttributeName (), serializableObject.getClass ().getName (), xmlWaveXPathValue);

            final Vector<String> configurationValues = waveConfigurationFile.getConfigurationValues (xmlWaveXPathValue);

            if (null != configurationValues)
            {
                final Vector<LocationId> value = new Vector<LocationId> ();

                for (final String configurationValue : configurationValues)
                {
                    if (WaveStringUtils.isNotBlank (configurationValue))
                    {
                        value.add (new LocationId (new UI32 (configurationValue)));
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
}
