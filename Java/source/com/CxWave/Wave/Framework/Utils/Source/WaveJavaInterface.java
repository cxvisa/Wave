
package com.CxWave.Wave.Framework.Utils.Source;

import java.lang.annotation.Annotation;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveJavaInterface extends WaveJavaType
{
    private final String                          m_name;
    private final Map<String, WaveJavaInterface>  m_superInterfaces;
    private final Map<String, WaveJavaAnnotation> m_annotations;
    private final Map<String, WaveJavaInterface>  m_childInterfaces;
    private final Map<String, WaveJavaClass>      m_childClasses;

    public WaveJavaInterface (final String name)
    {
        m_name = name;
        m_superInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_annotations = new HashMap<String, WaveJavaAnnotation> ();
        m_childInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_childClasses = new HashMap<String, WaveJavaClass> ();
    }

    public String getName ()
    {
        return m_name;
    }

    public void addSuperInterfaces (final Vector<String> superInterfaceNames)
    {
        for (final String superInterfaceName : superInterfaceNames)
        {
            if (WaveStringUtils.isNotBlank (superInterfaceName))
            {
                final WaveJavaInterface waveJavaSuperInterface = WaveJavaSourceRepository.getWaveJavaInterface (superInterfaceName);

                WaveAssertUtils.waveAssert (null != waveJavaSuperInterface);

                m_superInterfaces.put (superInterfaceName, waveJavaSuperInterface);

                waveJavaSuperInterface.addChildInterface (this);
            }
        }
    }

    public Vector<String> getSuperInterfaceNames ()
    {
        final Vector<String> superInterfaceNames = new Vector<String> ();

        for (final String superInterfaceName : m_superInterfaces.keySet ())
        {
            if (WaveStringUtils.isNotBlank (superInterfaceName))
            {
                superInterfaceNames.add (superInterfaceName);
            }
            else
            {
                WaveAssertUtils.waveAssert ();
            }
        }

        return (superInterfaceNames);
    }

    public void addAnnotations (final Vector<String> annotationNames)
    {
        for (final String annotationName : annotationNames)
        {
            if (WaveStringUtils.isNotBlank (annotationName))
            {
                if ((annotationName.startsWith ("java.")) || (annotationName.startsWith ("javax.")))
                {
                    continue;
                }

                final WaveJavaAnnotation waveJavaAnnotation = WaveJavaSourceRepository.getWaveJavaAnnotation (annotationName);

                WaveAssertUtils.waveAssert (null != waveJavaAnnotation);

                m_annotations.put (annotationName, waveJavaAnnotation);
            }
        }
    }

    public Vector<String> getAnnotationNames ()
    {
        final Vector<String> annotationNames = new Vector<String> ();

        for (final String annotationName : m_annotations.keySet ())
        {
            if (WaveStringUtils.isNotBlank (annotationName))
            {
                annotationNames.add (annotationName);
            }
        }

        return (annotationNames);
    }

    public void addChildInterface (final WaveJavaInterface waveJavaInterface)
    {
        m_childInterfaces.put (waveJavaInterface.getName (), waveJavaInterface);
    }

    public void addChildClass (final WaveJavaClass waveJavaClass)
    {
        m_childClasses.put (waveJavaClass.getName (), waveJavaClass);
    }

    @Override
    public void compute ()
    {
        Class<?> reflectionClass = null;

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "Computing for Java Interface " + m_name, true, false);

        try
        {
            reflectionClass = Class.forName (m_name);
        }
        catch (final ClassNotFoundException e)
        {
            e.printStackTrace ();
            WaveAssertUtils.waveAssert ();
        }

        final Class<?>[] superInterfaces = reflectionClass.getInterfaces ();
        final Vector<String> superInterfaceNames = new Vector<String> ();

        for (final Class<?> superInterface : superInterfaces)
        {
            superInterfaceNames.add (superInterface.getName ());
        }

        addSuperInterfaces (superInterfaceNames);

        final Annotation[] annotations = reflectionClass.getAnnotations ();
        final Vector<String> annotationNames = new Vector<String> ();

        for (final Annotation annotation : annotations)
        {
            annotationNames.add ((annotation.annotationType ()).getName ());
        }

        addAnnotations (annotationNames);
    }
}
