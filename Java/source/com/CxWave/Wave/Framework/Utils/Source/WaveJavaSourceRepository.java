/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Source;

import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.Attributes.Attribute;
import com.CxWave.Wave.Framework.Attributes.AttributesMap;
import com.CxWave.Wave.Framework.Attributes.Factory.AttributesFactory;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonAutoInstantiableService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.PrePhaseService;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveJavaSourceRepository
{
    private static WaveJavaSourceRepository       s_waveJavaSourceRepository = new WaveJavaSourceRepository ();

    private final Map<String, WaveJavaClass>      m_classes                  = new HashMap<String, WaveJavaClass> ();
    private final Map<String, WaveJavaInterface>  m_interfaces               = new HashMap<String, WaveJavaInterface> ();
    private final Map<String, WaveJavaEnum>       m_enums                    = new HashMap<String, WaveJavaEnum> ();
    private final Map<String, WaveJavaAnnotation> m_annotations              = new HashMap<String, WaveJavaAnnotation> ();
    private final Map<String, WaveJavaClass>      m_anonymousClasses         = new HashMap<String, WaveJavaClass> ();

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
        // Stage 1

        for (final WaveJavaClass waveJavaClass : m_classes.values ())
        {
            waveJavaClass.computeStage1 ();
        }

        for (final WaveJavaInterface wavejavaInterface : m_interfaces.values ())
        {
            wavejavaInterface.computeStage1 ();
        }

        for (final WaveJavaAnnotation waveJavaAnnotation : m_annotations.values ())
        {
            waveJavaAnnotation.computeStage1 ();
        }

        for (final WaveJavaEnum waveJavaEnum : m_enums.values ())
        {
            waveJavaEnum.computeStage1 ();
        }

        // Stage 2

        for (final WaveJavaClass waveJavaClass : m_classes.values ())
        {
            waveJavaClass.computeStage2 ();
        }

        for (final WaveJavaInterface wavejavaInterface : m_interfaces.values ())
        {
            wavejavaInterface.computeStage2 ();
        }

        for (final WaveJavaAnnotation waveJavaAnnotation : m_annotations.values ())
        {
            waveJavaAnnotation.computeStage2 ();
        }

        for (final WaveJavaEnum waveJavaEnum : m_enums.values ())
        {
            waveJavaEnum.computeStage2 ();
        }

        computeAttributeSpace ();
    }

    private void computeAttributeSpace ()
    {
        final Set<String> allDescendantsOfAttributeClass = WaveJavaSourceRepository.getAllDescendantsForClass (Attribute.class.getName ());

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Computing Attributes and supported Data Types.");

        for (final String attributeClassDescendant : allDescendantsOfAttributeClass)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Attribute Descendant : %s", attributeClassDescendant);

            Class<?> attributeClassDescendantClass = null;

            try
            {
                attributeClassDescendantClass = Class.forName (attributeClassDescendant);
            }
            catch (final ClassNotFoundException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "System could not load % class", attributeClassDescendant);
                WaveAssertUtils.waveAssert ();
            }

            WaveAssertUtils.waveAssert (null != attributeClassDescendantClass);

            AttributesFactory.addSupportedAttributeType (attributeClassDescendantClass);
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

    private Set<String> getAllDescendantsForClassInternal (final String className)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.getAllDescendants ());
        }
        else
        {
            return (new HashSet<String> ());
        }
    }

    public static Set<String> getAllDescendantsForClass (final String className)
    {
        return ((getInstance ()).getAllDescendantsForClassInternal (className));
    }

    private Set<String> getAllDescendantClassesForInterfaceInternal (final String interfaceName)
    {
        final WaveJavaInterface waveJavaInterface = m_interfaces.get (interfaceName);

        if (null != waveJavaInterface)
        {
            return (waveJavaInterface.getAllDescendantClasses ());
        }
        else
        {
            return (new HashSet<String> ());
        }
    }

    public static Set<String> getAllDescendantClassesForInterface (final String interfaceName)
    {
        return ((getInstance ()).getAllDescendantClassesForInterfaceInternal (interfaceName));
    }

    private Set<String> getAllDescendantClassesTypeNamesForInterfaceInternal (final String interfaceName)
    {
        final WaveJavaInterface waveJavaInterface = m_interfaces.get (interfaceName);

        if (null != waveJavaInterface)
        {
            return (waveJavaInterface.getAllDescendantClassesTypeNames ());
        }
        else
        {
            return (new HashSet<String> ());
        }
    }

    public static Set<String> getAllDescendantClassesTypeNamesForInterface (final String interfaceName)
    {
        return ((getInstance ()).getAllDescendantClassesTypeNamesForInterfaceInternal (interfaceName));
    }

    private Set<String> getAllDescendantEnumsForInterfaceInternal (final String interfaceName)
    {
        final WaveJavaInterface waveJavaInterface = m_interfaces.get (interfaceName);

        if (null != waveJavaInterface)
        {
            return (waveJavaInterface.getAllDescendantEnums ());
        }
        else
        {
            return (new HashSet<String> ());
        }
    }

    public static Set<String> getAllDescendantEnumsForInterface (final String interfaceName)
    {
        return ((getInstance ()).getAllDescendantEnumsForInterfaceInternal (interfaceName));
    }

    private Set<String> getAllDescendantEnumsTypeNamesForInterfaceInternal (final String interfaceName)
    {
        final WaveJavaInterface waveJavaInterface = m_interfaces.get (interfaceName);

        if (null != waveJavaInterface)
        {
            return (waveJavaInterface.getAllDescendantEnumsTypeNames ());
        }
        else
        {
            return (new HashSet<String> ());
        }
    }

    public static Set<String> getAllDescendantEnumsTypeNamesForInterface (final String interfaceName)
    {
        return ((getInstance ()).getAllDescendantEnumsTypeNamesForInterfaceInternal (interfaceName));
    }

    private Set<String> getAllDescendantsTypeNamesForClassInternal (final String className)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.getAllDescendantsTypeNames ());
        }
        else
        {
            return (new HashSet<String> ());
        }
    }

    public static Set<String> getAllDescendantsTypeNamesForClass (final String className)
    {
        return ((getInstance ()).getAllDescendantsTypeNamesForClassInternal (className));
    }

    private boolean isClassAnnotatedWithInternal (final String className, final String annotationName)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.isAnnotatedWith (annotationName));
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "WaveJavaSourceRepository.isClassAnnotatedWithInternal : Could not find class name %s", className);

            return (false);
        }
    }

    public static boolean isClassAnnotatedWith (final String className, final String annotationName)
    {
        return ((getInstance ()).isClassAnnotatedWithInternal (className, annotationName));
    }

    private Vector<String> getInheritanceHeirarchyForClassLatestFirstIncludingSelfInternal (final String className)
    {
        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_DEBUG, "WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirst : %s", className);

        final Vector<String> inheritanceHierarchy = new Vector<String> ();

        if (WaveStringUtils.isBlank (className))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_ERROR, "WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirst : Blank class name is not supported.");

            return (inheritanceHierarchy);
        }

        WaveJavaClass waveJavaClass = getWaveJavaClassInternal (className);

        if (null == waveJavaClass)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirst : %s is not known to Wave.", className);

            return (inheritanceHierarchy);
        }
        else
        {
            inheritanceHierarchy.add (className);
        }

        while (null != waveJavaClass)
        {
            final String superClassName = waveJavaClass.getSuperClassName ();

            if (null != superClassName)
            {
                inheritanceHierarchy.add (superClassName);

                waveJavaClass = getWaveJavaClassInternal (superClassName);
            }
            else
            {
                break;
            }
        }

        return (inheritanceHierarchy);
    }

    public static Vector<String> getInheritanceHeirarchyForClassLatestFirstIncludingSelf (final String className)
    {
        return ((getInstance ()).getInheritanceHeirarchyForClassLatestFirstIncludingSelfInternal (className));
    }

    public static AttributesMap getAttributesMapForInheritanceHierarchyForClass (final String className)
    {
        return ((getWaveJavaClass (className)).getAttributesMapForInheritanceHierarchy ());
    }

    private boolean isAderivativeOfSerializableObjectInternal (final String className)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.isADerivativeOfSerializableObject ());
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "WaveJavaSourceRepository.isAderivativeOfSerializableObject : Could not find class name %s", className);

            return (false);
        }
    }

    public static boolean isAderivativeOfSerializableObject (final String className)
    {
        return ((getInstance ()).isAderivativeOfSerializableObjectInternal (className));
    }

    private boolean isAderivativeOfWaveObjectManagerInternal (final String className)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.isADerivativeOfWaveObjectManager ());
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "WaveJavaSourceRepository.isAderivativeOfWaveObjectManagerInternal : Could not find class name %s", className);

            return (false);
        }
    }

    public static boolean isAderivativeOfWaveObjectManager (final String className)
    {
        return ((getInstance ()).isAderivativeOfWaveObjectManagerInternal (className));
    }

    private boolean isAderivativeOfWaveManagedObjectInternal (final String className)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.isADerivativeOfWaveManagedObject ());
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "WaveJavaSourceRepository.isAderivativeOfWaveManagedObjectInternal : Could not find class name %s", className);

            return (false);
        }
    }

    public static boolean isAderivativeOfWaveManagedObject (final String className)
    {
        return ((getInstance ()).isAderivativeOfWaveManagedObjectInternal (className));
    }

    private boolean isAderivativeOfWaveWorkerInternal (final String className)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.isADerivativeOfWaveWorker ());
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "WaveJavaSourceRepository.isAderivativeOfWaveWorkerInternal : Could not find class name %s", className);

            return (false);
        }
    }

    public static boolean isAderivativeOfWaveWorker (final String className)
    {
        return ((getInstance ()).isAderivativeOfWaveWorkerInternal (className));
    }

    public static Vector<Method> getAllMethodsInInheritanceHierarchyForClass (final String className)
    {
        final Vector<Method> allMethodsInInheritanceHierarchy = new Vector<Method> ();

        final Vector<String> inheritanceHierarchyForClassLatestFirstIncludingSelf = getInheritanceHeirarchyForClassLatestFirstIncludingSelf (className);

        WaveAssertUtils.waveAssert (null != inheritanceHierarchyForClassLatestFirstIncludingSelf);

        for (final String classNameInInheritanceHierarchy : inheritanceHierarchyForClassLatestFirstIncludingSelf)
        {
            final WaveJavaClass waveJavaClass = getWaveJavaClass (classNameInInheritanceHierarchy);

            WaveAssertUtils.waveAssert (null != waveJavaClass);
        }

        return (allMethodsInInheritanceHierarchy);
    }

    private Map<Class<?>, Method> getMessageHandlersInInheritanceHierarchyPreferringLatestInternal (final String className)
    {
        final WaveJavaClass waveJavaClass = m_classes.get (className);

        if (null != waveJavaClass)
        {
            return (waveJavaClass.getMessageHandlersInInheritanceHierarchyPreferringLatest ());
        }
        else
        {
            return (null);
        }
    }

    public static Map<Class<?>, Method> getMessageHandlersInInheritanceHierarchyPreferringLatest (final String className)
    {
        return ((getInstance ()).getMessageHandlersInInheritanceHierarchyPreferringLatestInternal (className));
    }

    public static Vector<String> getWorkerClassNamesForClass (final String waveJavaClassName)
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (waveJavaClassName);

        if (null == waveJavaClass)
        {
            return (new Vector<String> ());
        }

        return (waveJavaClass.getWorkerClassNames ());
    }

    public static int getWorkerClassCardinality (final String waveJavaClassName, final String workerClassName)
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (waveJavaClassName);

        if (null == waveJavaClass)
        {
            WaveAssertUtils.waveAssert ();
        }

        return (waveJavaClass.getWorkerClassCardinality (workerClassName));
    }

    public static WaveWorkerPriority getWorkerClassProiority (final String waveJavaClassName, final String workerClassName)
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (waveJavaClassName);

        if (null == waveJavaClass)
        {
            WaveAssertUtils.waveAssert ();
        }

        return (waveJavaClass.getWorkerClassPriority (workerClassName));
    }

    public static boolean waveObjectManagerIsADerivativeOf (final String derivedFromClassName)
    {
        return (WaveJavaClass.waveObjectManagerIsADerivativeOf (derivedFromClassName));
    }

    public static boolean waveWorkerIsADerivativeOf (final String derivedFromClassName)
    {
        return (WaveJavaClass.waveWorkerIsADerivativeOf (derivedFromClassName));
    }

    public static boolean waveManagedObjectIsADerivativeOf (final String derivedFromClassName)
    {
        return (WaveJavaClass.waveManagedObjectIsADerivativeOf (derivedFromClassName));
    }

    public static boolean waveMessageIsADerivativeOf (final String derivedFromClassName)
    {
        return (WaveJavaClass.waveMessageIsADerivativeOf (derivedFromClassName));
    }

    public static boolean waveSynchronousLinearSequencerContextIsADerivativeOf (final String derivedFromClassName)
    {
        return (WaveJavaClass.waveSynchronousLinearSequencerContextIsADerivativeOf (derivedFromClassName));
    }

    public static boolean waveLinearSequencerContextIsADerivativeOf (final String derivedFromClassName)
    {
        return (WaveJavaClass.waveLinearSequencerContextIsADerivativeOf (derivedFromClassName));
    }

    public static Method getMethodForWaveLinearSequencerStepInWaveJavaClass (final String waveJavaClassName, final String waveLinearSequencerStepName)
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (waveJavaClassName);

        if (null == waveJavaClass)
        {
            return (null);
        }

        return (waveJavaClass.getMethodForWaveLinearSequencerStep (waveLinearSequencerStepName));
    }

    public static Method getMethodForWaveSynchronousLinearSequencerStepInWaveJavaClass (final String waveJavaClassName, final String waveSynchronousLinearSequencerStepName)
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (waveJavaClassName);

        if (null == waveJavaClass)
        {
            return (null);
        }

        return (waveJavaClass.getMethodForWaveSynchronousLinearSequencerStep (waveSynchronousLinearSequencerStepName));
    }

    public static Method getMethodForWaveMessageCallbackInWaveJavaClass (final String waveJavaClassName, final String waveMessageCallbackName)
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (waveJavaClassName);

        if (null == waveJavaClass)
        {
            return (null);
        }

        return (waveJavaClass.getMethodForWaveMessageCallback (waveMessageCallbackName));
    }

    public static Method getMethodForWaveTimerExpirationHandlerInWaveJavaClass (final String waveJavaClassName, final String waveTimerExpirationHandlerName)
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (waveJavaClassName);

        if (null == waveJavaClass)
        {
            return (null);
        }

        return (waveJavaClass.getMethodForWaveTimerExpirationHandler (waveTimerExpirationHandlerName));
    }

    public static Set<String> getAllObjectManagerClassNames ()
    {
        final WaveJavaClass waveJavaClass = getWaveJavaClass (WaveObjectManager.class.getName ());

        WaveAssertUtils.waveAssert (null != waveJavaClass);

        final Set<String> allDescendantsForWaveObjectManager = getAllDescendantsForClass (waveJavaClass.getName ());

        return (allDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllInstantiableObjectManagerClassNames ()
    {
        final Set<String> allDescendantsForWaveObjectManager = getAllObjectManagerClassNames ();

        final Set<String> allInstantiableDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String descendantForWaveObjectManager : allDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForWaveObjectManagerDescendant = getWaveJavaClass (descendantForWaveObjectManager);

            if (null == waveJavaClassForWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllInstantiableObjectManagerClassNames : %s class could not be found.", descendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForWaveObjectManagerDescendant.isAnnotatedWith (NonOM.class.getName ())))
            {
                allInstantiableDescendantsForWaveObjectManager.add (descendantForWaveObjectManager);
            }
        }

        return (allInstantiableDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllAutoInstantiableObjectManagerClassNames ()
    {
        final Set<String> allInstantiableDescendantsForWaveObjectManager = getAllInstantiableObjectManagerClassNames ();

        final Set<String> allAutoInstantiablePrePhaseDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String instantiableDescendantForWaveObjectManager : allInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForInstantiableWaveObjectManagerDescendant = getWaveJavaClass (instantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllAutoInstantiablePrePhaseObjectManagerClassNames : %s class could not be found.", instantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForInstantiableWaveObjectManagerDescendant.isAnnotatedWith (NonAutoInstantiableService.class.getName ())))
            {
                allAutoInstantiablePrePhaseDescendantsForWaveObjectManager.add (instantiableDescendantForWaveObjectManager);
            }
        }

        return (allAutoInstantiablePrePhaseDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllInstantiablePrePhaseObjectManagerClassNames ()
    {
        final Set<String> allInstantiableDescendantsForWaveObjectManager = getAllInstantiableObjectManagerClassNames ();

        final Set<String> allInstantiablePrePhaseDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String instantiableDescendantForWaveObjectManager : allInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForInstantiableWaveObjectManagerDescendant = getWaveJavaClass (instantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllInstantiablePrePhaseObjectManagerClassNames : %s class could not be found.", instantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (waveJavaClassForInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ()))
            {
                allInstantiablePrePhaseDescendantsForWaveObjectManager.add (instantiableDescendantForWaveObjectManager);
            }
        }

        return (allInstantiablePrePhaseDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllInstantiableNonPrePhaseObjectManagerClassNames ()
    {
        final Set<String> allInstantiableDescendantsForWaveObjectManager = getAllInstantiableObjectManagerClassNames ();

        final Set<String> allInstantiableNonPrePhaseDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String instantiableDescendantForWaveObjectManager : allInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForInstantiableWaveObjectManagerDescendant = getWaveJavaClass (instantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllInstantiableNonPrePhaseObjectManagerClassNames : %s class could not be found.", instantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ())))
            {
                allInstantiableNonPrePhaseDescendantsForWaveObjectManager.add (instantiableDescendantForWaveObjectManager);
            }
        }

        return (allInstantiableNonPrePhaseDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllAutoInstantiablePrePhaseObjectManagerClassNames ()
    {
        final Set<String> allAutoInstantiableDescendantsForWaveObjectManager = getAllAutoInstantiableObjectManagerClassNames ();

        final Set<String> allAutoInstantiablePrePhaseDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String autoInstantiableDescendantForWaveObjectManager : allAutoInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForAutoInstantiableWaveObjectManagerDescendant = getWaveJavaClass (autoInstantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForAutoInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllAutoInstantiablePrePhaseObjectManagerClassNames : %s class could not be found.", autoInstantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (waveJavaClassForAutoInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ()))
            {
                allAutoInstantiablePrePhaseDescendantsForWaveObjectManager.add (autoInstantiableDescendantForWaveObjectManager);
            }
        }

        return (allAutoInstantiablePrePhaseDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllAutoInstantiableNonPrePhaseObjectManagerClassNames ()
    {
        final Set<String> allAutoInstantiableDescendantsForWaveObjectManager = getAllAutoInstantiableObjectManagerClassNames ();

        final Set<String> allAutoInstantiableNonPrePhaseDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String autoInstantiableDescendantForWaveObjectManager : allAutoInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForAutoInstantiableWaveObjectManagerDescendant = getWaveJavaClass (autoInstantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForAutoInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllAutoInstantiableNonPrePhaseObjectManagerClassNames : %s class could not be found.", autoInstantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForAutoInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ())))
            {
                allAutoInstantiableNonPrePhaseDescendantsForWaveObjectManager.add (autoInstantiableDescendantForWaveObjectManager);
            }
        }

        return (allAutoInstantiableNonPrePhaseDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllInstantiableNonPrePhaseNativeObjectManagerClassNames ()
    {
        final Set<String> allInstantiableDescendantsForWaveObjectManager = getAllInstantiableObjectManagerClassNames ();

        final Set<String> allInstantiableNonPrePhaseNativeDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String instantiableDescendantForWaveObjectManager : allInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForInstantiableWaveObjectManagerDescendant = getWaveJavaClass (instantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllInstantiableNonPrePhaseNativeObjectManagerClassNames : %s class could not be found.", instantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ())))
            {
                if (waveJavaClassForInstantiableWaveObjectManagerDescendant.isAnnotatedWith (NativeService.class.getName ()))
                {
                    allInstantiableNonPrePhaseNativeDescendantsForWaveObjectManager.add (instantiableDescendantForWaveObjectManager);
                }
            }
        }

        return (allInstantiableNonPrePhaseNativeDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllAutoInstantiableNonPrePhaseNativeObjectManagerClassNames ()
    {
        final Set<String> allAutoInstantiableDescendantsForWaveObjectManager = getAllAutoInstantiableObjectManagerClassNames ();

        final Set<String> allAutoInstantiableNonPrePhaseNativeDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String autoInstantiableDescendantForWaveObjectManager : allAutoInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForAutoInstantiableWaveObjectManagerDescendant = getWaveJavaClass (autoInstantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForAutoInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllAutoInstantiableNonPrePhaseNativeObjectManagerClassNames : %s class could not be found.", autoInstantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForAutoInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ())))
            {
                if (waveJavaClassForAutoInstantiableWaveObjectManagerDescendant.isAnnotatedWith (NativeService.class.getName ()))
                {
                    allAutoInstantiableNonPrePhaseNativeDescendantsForWaveObjectManager.add (autoInstantiableDescendantForWaveObjectManager);
                }
            }
        }

        return (allAutoInstantiableNonPrePhaseNativeDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllInstantiableNonPrePhaseNonNativeObjectManagerClassNames ()
    {
        final Set<String> allInstantiableDescendantsForWaveObjectManager = getAllInstantiableObjectManagerClassNames ();

        final Set<String> allInstantiableNonPrePhaseNonNativeDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String instantiableDescendantForWaveObjectManager : allInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForInstantiableWaveObjectManagerDescendant = getWaveJavaClass (instantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllInstantiableNonPrePhaseNonNativeObjectManagerClassNames : %s class could not be found.", instantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ())))
            {
                if (!(waveJavaClassForInstantiableWaveObjectManagerDescendant.isAnnotatedWith (NativeService.class.getName ())))
                {
                    allInstantiableNonPrePhaseNonNativeDescendantsForWaveObjectManager.add (instantiableDescendantForWaveObjectManager);
                }
            }
        }

        return (allInstantiableNonPrePhaseNonNativeDescendantsForWaveObjectManager);
    }

    public static Set<String> getAllAutoInstantiableNonPrePhaseNonNativeObjectManagerClassNames ()
    {
        final Set<String> allAutoInstantiableDescendantsForWaveObjectManager = getAllAutoInstantiableObjectManagerClassNames ();

        final Set<String> allAutoInstantiableNonPrePhaseNonNativeDescendantsForWaveObjectManager = new HashSet<String> ();

        for (final String autoInstantiableDescendantForWaveObjectManager : allAutoInstantiableDescendantsForWaveObjectManager)
        {
            final WaveJavaClass waveJavaClassForAutoInstantiableWaveObjectManagerDescendant = getWaveJavaClass (autoInstantiableDescendantForWaveObjectManager);

            if (null == waveJavaClassForAutoInstantiableWaveObjectManagerDescendant)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaSourceRepository.getAllAutoInstantiableNonPrePhaseNonNativeObjectManagerClassNames : %s class could not be found.", autoInstantiableDescendantForWaveObjectManager);

                WaveAssertUtils.waveAssert ();
            }

            if (!(waveJavaClassForAutoInstantiableWaveObjectManagerDescendant.isAnnotatedWith (PrePhaseService.class.getName ())))
            {
                if (!(waveJavaClassForAutoInstantiableWaveObjectManagerDescendant.isAnnotatedWith (NativeService.class.getName ())))
                {
                    allAutoInstantiableNonPrePhaseNonNativeDescendantsForWaveObjectManager.add (autoInstantiableDescendantForWaveObjectManager);
                }
            }
        }

        return (allAutoInstantiableNonPrePhaseNonNativeDescendantsForWaveObjectManager);
    }
}
