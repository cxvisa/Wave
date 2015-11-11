/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.util.Set;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public abstract class Attribute
{
    private Object                m_lastValue;

    protected ReflectionAttribute m_reflectionAttribute;

    public Attribute ()
    {
        m_lastValue = null;
        m_reflectionAttribute = null;
    }

    public Attribute (final ReflectionAttribute reflectionAttribute)
    {
        m_lastValue = null;
        m_reflectionAttribute = reflectionAttribute;
    }

    public ReflectionAttribute getReflectionAttribute ()
    {
        return (m_reflectionAttribute);
    }

    private Field getReflectionField ()
    {
        return (m_reflectionAttribute.getField ());
    }

    public void setReflectionField (final ReflectionAttribute reflectionAttribute)
    {
        m_reflectionAttribute = reflectionAttribute;
    }

    public Object getLastValue ()
    {
        return (m_lastValue);
    }

    public void setLastValue (final Object lastValue)
    {
        m_lastValue = lastValue;
    }

    public Object getCurrentValue (final Object owner)
    {
        Object currentValue = null;
        final Field field = getReflectionField ();

        if ((null != owner) && (null != field))
        {
            try
            {
                currentValue = field.get (owner);
            }
            catch (IllegalArgumentException | IllegalAccessException e)
            {
                e.printStackTrace ();

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not get current Value via field.  Class Name : %s, Field Name : %s", (owner.getClass ()).getName (), m_reflectionAttribute.getAttributeName ());
                WaveAssertUtils.waveAssert ();
            }
        }

        return (currentValue);
    }

    public abstract Set<String> getSupportedDataTypes ();

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

            reflectionField.set (serializableObject, value);
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Attribute.loadValueFromPlainString : Attribute loading failed for Field : %s, Class : %s, value : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), value, e.toString ());
            WaveAssertUtils.waveAssert ();
        }
    }

    public String toPlainString (final SerializableObject serializableObject)
    {
        WaveAssertUtils.waveAssert (null != serializableObject);

        final Field reflectionField = m_reflectionAttribute.getField ();

        WaveAssertUtils.waveAssert (null != reflectionField);

        Object object = null;
        String plainString = "";

        try
        {
            // WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Attribute.loadValueFromPlainString : Attribute loading
            // for Field : %s, Class : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass
            // ()).getName ());

            object = reflectionField.get (serializableObject);
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Attribute.loadValueFromPlainString : Attribute loading failed for Field : %s, Class : %s, Status : %s", m_reflectionAttribute.getAttributeName (), (serializableObject.getClass ()).getName (), e.toString ());
            WaveAssertUtils.waveAssert ();
        }

        if (null != object)
        {
            plainString = object.toString ();
        }

        return (plainString);
    }

    public void loadValueFromWaveConfigurationFile (final WaveConfigurationFile waveConfigurationFile, final SerializableObject serializableObject, final String xmlWaveXPathPrefix)
    {
        WaveAssertUtils.waveAssert (null != waveConfigurationFile);

        WaveAssertUtils.waveAssert (null != serializableObject);

        final String xmlWaveXPathValue = getXmlWaveXPath (xmlWaveXPathPrefix);

        if (WaveStringUtils.isNotBlank (xmlWaveXPathValue))
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Field : %s, Class : %s, xmlWaveXPathValue : %s", m_reflectionAttribute.getAttributeName (), serializableObject.getClass ().getName (), xmlWaveXPathValue);

            final String configurationValue = waveConfigurationFile.getConfigurationValue (xmlWaveXPathValue);

            if (WaveStringUtils.isNotBlank (configurationValue))
            {
                loadValueFromPlainString (configurationValue, serializableObject);
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

    public String getXmlWaveXPath (final String xmlWaveXPathPrefix)
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
            }
            else if (WaveStringUtils.isNotBlank (xmlWaveXPathValue))
            {
                if (WaveStringUtils.isNotBlank (xmlWaveXPathPrefix))
                {
                    xmlWaveXPathValue = xmlWaveXPathPrefix + "." + xmlWaveXPathValue;
                }
            }
        }

        return (xmlWaveXPathValue);
    }

    public void debugPrint (final SerializableObject serializableObject, String prefix)
    {
        if (null == serializableObject)
        {
            return;
        }

        if (null == prefix)
        {
            prefix = "";
        }

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "%s%s (%s) : %s", prefix, m_reflectionAttribute.getAttributeFieldName (), m_reflectionAttribute.getAttributeName (), toPlainString (serializableObject));
    }
}
