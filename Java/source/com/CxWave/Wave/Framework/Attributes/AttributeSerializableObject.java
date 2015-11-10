/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributeSerializableObject extends Attribute
{
    @Override
    public Set<String> getSupportedDataTypes ()
    {
        return (WaveJavaSourceRepository.getAllDescendantsTypeNamesForClass (SerializableObject.class.getName ()));
    }

    @Override
    public void loadValueFromWaveConfigurationFile (final WaveConfigurationFile waveConfigurationFile, final SerializableObject serializableObject)
    {
        WaveAssertUtils.waveAssert (null != waveConfigurationFile);

        WaveAssertUtils.waveAssert (null != serializableObject);

        final Field reflectionField = m_reflectionAttribute.getField ();

        WaveAssertUtils.waveAssert (null != reflectionField);

        try
        {
            Object object = (reflectionField.get (serializableObject));

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
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not find constructor with 0 arguments for Field Type : %s", fieldType.getName ());
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "    Please declare a constructor with no arguments and retry.");

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
                        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributeSerializableObject.loadValueFromWaveConfigurationFile:  Instantiating fieldType :%s failed.  Status : %s", fieldType.getName (), e.toString ());
                        WaveAssertUtils.waveAssert ();
                    }
                }
            }

            final SerializableObject serializableObjectForAttribute = (SerializableObject) object;

            WaveAssertUtils.waveAssert (null != serializableObject);

            reflectionField.set (serializableObject, serializableObjectForAttribute);

            serializableObjectForAttribute.loadFromWaveConfigurationFile (waveConfigurationFile);
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AttributeSerializableObject.loadValueFromWaveConfigurationFile : Attribute loading failed for Field : %s, Class : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }
}
