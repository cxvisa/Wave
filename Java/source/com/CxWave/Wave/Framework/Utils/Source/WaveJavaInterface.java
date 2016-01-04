
package com.CxWave.Wave.Framework.Utils.Source;

import java.lang.annotation.Annotation;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
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
    private final Map<String, WaveJavaEnum>       m_childEnums;
    private String                                m_typeName;

    public WaveJavaInterface (final String name)
    {
        m_name = name;
        m_superInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_annotations = new HashMap<String, WaveJavaAnnotation> ();
        m_childInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_childClasses = new HashMap<String, WaveJavaClass> ();
        m_childEnums = new HashMap<String, WaveJavaEnum> ();
    }

    public String getName ()
    {
        return m_name;
    }

    public String getTypeName ()
    {
        return (m_typeName);
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

    public void addChildEnum (final WaveJavaEnum waveJavaEnum)
    {
        m_childEnums.put (waveJavaEnum.getName (), waveJavaEnum);
    }

    @Override
    public void computeStage1 ()
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

        m_typeName = reflectionClass.getTypeName ();

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

    @Override
    public void computeStage2 ()
    {
    }

    public Set<String> getAllDescendantClasses ()
    {
        final Set<String> allDescendantClassesSet = new HashSet<String> ();

        for (final Map.Entry<String, WaveJavaClass> descendant : m_childClasses.entrySet ())
        {
            allDescendantClassesSet.add (descendant.getKey ());

            allDescendantClassesSet.addAll ((descendant.getValue ()).getAllDescendants ());
        }

        for (final Map.Entry<String, WaveJavaInterface> descendantInterface : m_childInterfaces.entrySet ())
        {
            allDescendantClassesSet.addAll ((descendantInterface.getValue ()).getAllDescendantClasses ());
        }

        return (allDescendantClassesSet);
    }

    public Set<String> getAllDescendantClassesTypeNames ()
    {
        final Set<String> allDescendantClassesTypeNamesSet = new HashSet<String> ();

        for (final Map.Entry<String, WaveJavaClass> descendant : m_childClasses.entrySet ())
        {
            allDescendantClassesTypeNamesSet.add ((descendant.getValue ()).getTypeName ());

            allDescendantClassesTypeNamesSet.addAll ((descendant.getValue ()).getAllDescendantsTypeNames ());
        }

        for (final Map.Entry<String, WaveJavaInterface> descendantInterface : m_childInterfaces.entrySet ())
        {
            allDescendantClassesTypeNamesSet.addAll ((descendantInterface.getValue ()).getAllDescendantClassesTypeNames ());
        }

        return (allDescendantClassesTypeNamesSet);
    }

    public Set<String> getAllDescendantEnums ()
    {
        final Set<String> allDescendantEnumsSet = new HashSet<String> ();

        for (final Map.Entry<String, WaveJavaEnum> descendant : m_childEnums.entrySet ())
        {
            allDescendantEnumsSet.add (descendant.getKey ());
        }

        for (final Map.Entry<String, WaveJavaInterface> descendantInterface : m_childInterfaces.entrySet ())
        {
            allDescendantEnumsSet.addAll ((descendantInterface.getValue ()).getAllDescendantEnums ());
        }

        return (allDescendantEnumsSet);
    }

    public Set<String> getAllDescendantEnumsTypeNames ()
    {
        final Set<String> allDescendantEnumsTypeNamesSet = new HashSet<String> ();

        for (final Map.Entry<String, WaveJavaEnum> descendant : m_childEnums.entrySet ())
        {
            allDescendantEnumsTypeNamesSet.add ((descendant.getValue ()).getTypeName ());
        }

        for (final Map.Entry<String, WaveJavaInterface> descendantInterface : m_childInterfaces.entrySet ())
        {
            allDescendantEnumsTypeNamesSet.addAll ((descendantInterface.getValue ()).getAllDescendantEnumsTypeNames ());
        }

        return (allDescendantEnumsTypeNamesSet);
    }
}
