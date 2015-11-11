/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
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
    public void loadValueFromWaveConfigurationFile (final WaveConfigurationFile waveConfigurationFile, final SerializableObject serializableObject, final String xmlWaveXPathPrefix)
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

            WaveAssertUtils.waveAssert (null != serializableObjectForAttribute);

            reflectionField.set (serializableObject, serializableObjectForAttribute);

            setXmlWaveXPathOnSerializableObject (serializableObjectForAttribute);

            serializableObjectForAttribute.loadFromWaveConfigurationFile (waveConfigurationFile, xmlWaveXPathPrefix);
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AttributeSerializableObject.loadValueFromWaveConfigurationFile : Attribute loading failed for Field : %s, Class : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }

    private void setXmlWaveXPathOnSerializableObject (final SerializableObject serializableObject)
    {
        final Field reflectionField = m_reflectionAttribute.getField ();

        WaveAssertUtils.waveAssert (null != reflectionField);

        final Annotation annotation = reflectionField.getAnnotation (XmlWaveXPath.class);

        String xmlWaveXPathValue = null;
        String xmlWaveXPathAbsoluteValue = null;

        if (null != annotation)
        {
            final XmlWaveXPath xmlWaveXPath = (XmlWaveXPath) annotation;

            WaveAssertUtils.waveAssert (null != xmlWaveXPath);

            xmlWaveXPathValue = xmlWaveXPath.path ();
            xmlWaveXPathAbsoluteValue = xmlWaveXPath.absolutePath ();

            // Give preference to absolute XML Wave XPATH.

            if (WaveStringUtils.isNotBlank (xmlWaveXPathAbsoluteValue))
            {
                xmlWaveXPathValue = xmlWaveXPathAbsoluteValue;

                serializableObject.setAttributeXmlWaveXPath (xmlWaveXPathValue, true);
            }
            else
            {
                serializableObject.setAttributeXmlWaveXPath (xmlWaveXPathValue, false);
            }
        }
    }

    @Override
    public void debugPrint (final SerializableObject serializableObject, final String prefix)
    {
        WaveAssertUtils.waveAssert (null != serializableObject);

        final Field reflectionField = m_reflectionAttribute.getField ();

        WaveAssertUtils.waveAssert (null != reflectionField);

        try
        {
            final Object object = (reflectionField.get (serializableObject));

            if (null == object)
            {

            }
            else
            {
                final SerializableObject serializableObjectForAttribute = (SerializableObject) object;

                WaveAssertUtils.waveAssert (null != serializableObjectForAttribute);

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "%s%s (%s) (%s) :", prefix, m_reflectionAttribute.getAttributeFieldName (), m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName ());

                serializableObjectForAttribute.debugPrint ("|   " + prefix);
            }
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "AttributeSerializableObject.loadValueFromWaveConfigurationFile : Attribute loading failed for Field : %s, Class : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }
}
