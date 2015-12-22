/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.lang.annotation.Annotation;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.CxWave.Wave.Framework.Attributes.AttributesMap;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class SerializableObject
{
    @NonSerializable
    protected AttributesMap m_attributesMap                  = null;

    @NonSerializable
    private boolean         m_isXmlWaveXPathForClassAbsolute = false;

    protected SerializableObject ()
    {
    }

    public boolean getIsPreparedForSerialization ()
    {
        if (null != m_attributesMap)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    protected void prepareForSerialization ()
    {
        if (null == m_attributesMap)
        {
            final String className = (getClass ()).getName ();

            final AttributesMap attributesMap = WaveJavaSourceRepository.getAttributesMapForInheritanceHierarchyForClass (className);

            WaveAssertUtils.waveAssert (null != attributesMap);

            m_attributesMap = attributesMap;

            m_attributesMap.setSerializableObject (this);
        }
    }

    public void setAttributeXmlWaveXPath (final String xmlWaveXPath, final boolean isAbsolute)
    {
        prepareForSerialization ();

        WaveAssertUtils.waveAssert (null != m_attributesMap);

        m_attributesMap.setWaveXmlXPathViaAttribute (xmlWaveXPath);
        m_attributesMap.setIsWaveXmlXPathViaAttributeAbsolute (isAbsolute);
    }

    public void loadFromWaveConfigurationFile (final String waveConfigurationFilePath)
    {
        prepareForSerialization ();

        m_attributesMap.loadFromWaveConfigurationFile (waveConfigurationFilePath, "");
    }

    public void loadFromWaveConfigurationFile (final String waveConfigurationFilePath, final String xmlWaveXPathPrefix)
    {
        prepareForSerialization ();

        m_attributesMap.loadFromWaveConfigurationFile (waveConfigurationFilePath, xmlWaveXPathPrefix);
    }

    public void loadFromWaveConfigurationFile (final WaveConfigurationFile waveConfigurationFile, final String xmlWaveXPathPrefix)
    {
        prepareForSerialization ();

        m_attributesMap.loadFromWaveConfigurationFile (waveConfigurationFile, xmlWaveXPathPrefix);
    }

    public String computeAndGetXmlWaveXPathForClass ()
    {
        final Class<?> classForSerializableObject = this.getClass ();

        WaveAssertUtils.waveAssert (null != classForSerializableObject);

        final Annotation annotation = classForSerializableObject.getAnnotation (XmlWaveXPath.class);

        String xmlWaveXPathValue = null;
        String xmlWaveXPathAbsoluteValue = null;
        String xmlWaveXPathEffectiveValue = null;

        if (null != annotation)
        {
            final XmlWaveXPath xmlWaveXPath = (XmlWaveXPath) annotation;

            WaveAssertUtils.waveAssert (null != xmlWaveXPath);

            final Class<?> annotationClass = xmlWaveXPath.annotationType ();

            WaveAssertUtils.waveAssert (null != annotationClass);

            Method pathMethod = null;
            Method absolutePathMethod = null;

            try
            {
                pathMethod = annotationClass.getDeclaredMethod ("path");
            }
            catch (NoSuchMethodException | SecurityException e)
            {
                WaveAssertUtils.waveAssert ();
            }

            try
            {
                absolutePathMethod = annotationClass.getDeclaredMethod ("absolutePath");
            }
            catch (NoSuchMethodException | SecurityException e)
            {
                WaveAssertUtils.waveAssert ();
            }

            WaveAssertUtils.waveAssert (null != pathMethod);
            WaveAssertUtils.waveAssert (null != absolutePathMethod);

            try
            {
                xmlWaveXPathValue = (String) (pathMethod.invoke (xmlWaveXPath));
            }
            catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
            {
                WaveAssertUtils.waveAssert ();
            }
            try
            {
                xmlWaveXPathAbsoluteValue = (String) (absolutePathMethod.invoke (xmlWaveXPath));
            }
            catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
            {
                WaveAssertUtils.waveAssert ();
            }
        }

        if (WaveStringUtils.isNotBlank (xmlWaveXPathAbsoluteValue))
        {
            xmlWaveXPathEffectiveValue = xmlWaveXPathAbsoluteValue;

            m_isXmlWaveXPathForClassAbsolute = true;
        }
        else if (WaveStringUtils.isNotBlank (xmlWaveXPathValue))
        {
            xmlWaveXPathEffectiveValue = xmlWaveXPathValue;

            m_isXmlWaveXPathForClassAbsolute = false;
        }

        return (xmlWaveXPathEffectiveValue);
    }

    public boolean getIsXmlWaveXPathForClassAbsolute ()
    {
        return m_isXmlWaveXPathForClassAbsolute;
    }

    public void setIsXmlWaveXPathForClassAbsolute (final boolean isXmlWaveXPathForClassAbsolute)
    {
        m_isXmlWaveXPathForClassAbsolute = isXmlWaveXPathForClassAbsolute;
    }

    public void debugPrint (final String prefix)
    {
        m_attributesMap.debugPrint (prefix);
    }

    public void debugPrint ()
    {
        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "%s :", (getClass ()).getName ());

        debugPrint ("|-> ");
    }

    public void serializeTo (final StringBuffer stringBuffer)
    {
        prepareForSerialization ();

        m_attributesMap.serializeTo (stringBuffer);
    }

    public void loadFromSerializableObject (final SerializableObject serializableObject)
    {
        prepareForSerialization ();
        serializableObject.prepareForSerialization ();

        m_attributesMap.copyFrom (serializableObject.m_attributesMap);
    }

    public boolean isPreparedForSerialization ()
    {
        return (null != m_attributesMap);
    }
}
