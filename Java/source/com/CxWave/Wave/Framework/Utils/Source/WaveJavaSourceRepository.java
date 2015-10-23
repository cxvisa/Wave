/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Source;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveJavaSourceRepository
{
    private static WaveJavaSourceRepository s_waveJavaSourceRepository = new WaveJavaSourceRepository ();

    private final Map<String, WaveJavaClass>      m_classes          = new HashMap<String, WaveJavaClass> ();
    private final Map<String, WaveJavaInterface>  m_interfaces       = new HashMap<String, WaveJavaInterface> ();
    private final Map<String, WaveJavaEnum>       m_enums            = new HashMap<String, WaveJavaEnum> ();
    private final Map<String, WaveJavaAnnotation> m_annotations      = new HashMap<String, WaveJavaAnnotation> ();
    private final Map<String, WaveJavaClass>      m_anonymousClasses = new HashMap<String, WaveJavaClass> ();

    private WaveJavaSourceRepository ()
    {
    }

    public static WaveJavaSourceRepository getInstance ()
    {
        WaveAssertUtils.waveAssert (null != s_waveJavaSourceRepository);

        return (s_waveJavaSourceRepository);
    }

    private WaveJavaClass getWaveJavaClassInternal (final String waveJavaClassName)
    {
        return (m_classes.get (waveJavaClassName));
    }

    public static WaveJavaClass getWaveJavaClass (final String waveJavaClassName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaClassInternal (waveJavaClassName));
    }

    private WaveJavaInterface getWaveJavaInterfaceInternal (final String waveJavaInterfaceName)
    {
        return (m_interfaces.get (waveJavaInterfaceName));
    }

    public static WaveJavaInterface getWaveJavaInterface (final String waveJavaInterfaceName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaInterfaceInternal (waveJavaInterfaceName));
    }

    private WaveJavaEnum getWaveJavaEnumInternal (final String waveJavaEnumName)
    {
        return (m_enums.get (waveJavaEnumName));
    }

    public static WaveJavaEnum getWaveJavaEnum (final String waveJavaEnumName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaEnumInternal (waveJavaEnumName));
    }

    private WaveJavaAnnotation getWaveJavaAnnotationInternal (final String waveJavaAnnotationName)
    {
        return (m_annotations.get (waveJavaAnnotationName));
    }

    public static WaveJavaAnnotation getWaveJavaAnnotation (final String waveJavaAnnotationName)
    {
        return ((WaveJavaSourceRepository.getInstance ()).getWaveJavaAnnotationInternal (waveJavaAnnotationName));
    }

    private void addJavaReflectionClassInternal (final Class<?> javaReflectionClass)
    {
        WaveAssertUtils.waveAssert (null != javaReflectionClass);

        final String javaReflectionClassCanonicalName = javaReflectionClass.getName ();

        if (javaReflectionClass.isAnnotation ())
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "    " + javaReflectionClassCanonicalName + " : Adding Annotation.", true, false);

            final WaveJavaAnnotation waveJavaAnnotation = new WaveJavaAnnotation (javaReflectionClass.getName ());

            WaveAssertUtils.waveAssert (null != waveJavaAnnotation);

            m_annotations.put (waveJavaAnnotation.getName (), waveJavaAnnotation);
        }
        else if (javaReflectionClass.isEnum ())
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "    " + javaReflectionClassCanonicalName + " : Adding Enum.", true, false);

            final WaveJavaEnum waveJavaEnum = new WaveJavaEnum (javaReflectionClass.getName ());

            WaveAssertUtils.waveAssert (null != waveJavaEnum);

            m_enums.put (waveJavaEnum.getName (), waveJavaEnum);
        }
        else if (javaReflectionClass.isInterface ())
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "    " + javaReflectionClassCanonicalName + " : Adding Interface.", true, false);

            final WaveJavaInterface waveJavaInterface = new WaveJavaInterface (javaReflectionClass.getName ());

            WaveAssertUtils.waveAssert (null != waveJavaInterface);

            m_interfaces.put (waveJavaInterface.getName (), waveJavaInterface);
        }
        else if (null == javaReflectionClassCanonicalName)
        {
            final String javaReflectionClassName = javaReflectionClass.getName ();

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN, "    " + javaReflectionClassCanonicalName + " : Adding Anonymous Class.", true, false);

            final WaveJavaClass waveJavaClass = new WaveJavaClass (javaReflectionClassName);

            WaveAssertUtils.waveAssert (null != waveJavaClass);

            m_anonymousClasses.put (javaReflectionClassName, waveJavaClass);
        }
        else
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "    " + javaReflectionClassCanonicalName + " : Adding Class.", true, false);

            final WaveJavaClass waveJavaClass = new WaveJavaClass (javaReflectionClass.getName ());

            WaveAssertUtils.waveAssert (null != waveJavaClass);

            m_classes.put (waveJavaClass.getName (), waveJavaClass);
        }
    }

    public static void addJavaReflectionClass (final Class<?> javaReflectionClass)
    {
        (WaveJavaSourceRepository.getInstance ()).addJavaReflectionClassInternal (javaReflectionClass);
    }

    public static void addJavaReflectionClass (final String javaReflectionClassName)
    {
        Class<?> javaReflectionClass = null;

        try
        {
            javaReflectionClass = Class.forName (javaReflectionClassName);
        }
        catch (final ClassNotFoundException e)
        {
            e.printStackTrace ();

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "Could not load class : " + javaReflectionClassName, true, false);

            WaveAssertUtils.waveAssert ();
        }

        WaveAssertUtils.waveAssert (null != javaReflectionClass);

        addJavaReflectionClass (javaReflectionClass);
    }

    private void computeInternal ()
    {
        for (final WaveJavaClass waveJavaClass : m_classes.values ())
        {
            waveJavaClass.compute ();
        }
    }

    public static void compute ()
    {
        (WaveJavaSourceRepository.getInstance ()).computeInternal ();
    }

    public static void initialize ()
    {
        final List<String> allAvailableClasses = SourceUtils.getListOfAllAvailableClasses ();

        for (final String availableClass : allAvailableClasses)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "Adding Java Reflection Class : " + availableClass, true, false);

            addJavaReflectionClass (availableClass);
        }

        compute ();
    }
}