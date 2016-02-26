/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Source;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.Vector;

import com.CxWave.Wave.Framework.Attributes.AttributesMap;
import com.CxWave.Wave.Framework.Attributes.ReflectionAttribute;
import com.CxWave.Wave.Framework.Attributes.ReflectionAttributesMap;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.WaveManagedObject;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonEventHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageCallback;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSequencerStep;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonTimerExpirationHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.SerializableAttribute;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveSynchronousLinearSequencerContext;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Shell.ShellBase;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;
import com.CxWave.Wave.Shell.Annotations.ShellRoot;
import com.CxWave.Wave.Shell.Annotations.ShellSubordinate;

public class WaveJavaClass extends WaveJavaType
{
    private final String                                m_name;
    private final Map<String, WaveJavaInterface>        m_superInterfaces;
    private final Map<String, WaveJavaAnnotation>       m_annotations;
    private WaveJavaClass                               m_superClass;
    private final Map<String, WaveJavaClass>            m_childClasses;
    private final Map<String, WaveJavaClass>            m_anonymousClasses;
    private WaveJavaClass                               m_declaringClass;
    private final ReflectionAttributesMap               m_serializationReflectionAttributesMapForDeclaredFields;
    private String                                      m_typeName;
    private final Map<Class<?>, Method>                 m_messageHandlers;
    private final Map<Class<?>, Method>                 m_eventHandlers;
    private final Map<String, Integer>                  m_ownedWorkerClassNamesCadinalityMap;
    private final Map<String, WaveWorkerPriority>       m_ownedWorkerClassNamesPriorityMap;
    private final Set<String>                           m_ownedEventClasses;
    private final Map<String, Method>                   m_waveLinearSequencerSteps;
    private final Map<String, Method>                   m_waveSynchronousLinearSequencerSteps;
    private final Map<String, Method>                   m_waveMessageCallbacks;
    private final Map<String, Method>                   m_waveTimerExpirationHandlers;
    private final Map<String, Method>                   m_waveEventHandlers;

    private static Map<Class<?>, Map<String, Method>>   s_shellCommandHandlerMethodsByClass = new HashMap<Class<?>, Map<String, Method>> ();
    private static Map<Class<?>, Map<String, Class<?>>> s_shellSubordinatesByClass          = new HashMap<Class<?>, Map<String, Class<?>>> ();

    private static Class<?>                             s_shellRootClass                    = null;

    public WaveJavaClass (final String name)
    {
        m_name = name;
        m_superInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_annotations = new HashMap<String, WaveJavaAnnotation> ();
        m_childClasses = new HashMap<String, WaveJavaClass> ();
        m_anonymousClasses = new HashMap<String, WaveJavaClass> ();
        m_serializationReflectionAttributesMapForDeclaredFields = new ReflectionAttributesMap ();
        m_messageHandlers = new HashMap<Class<?>, Method> ();
        m_eventHandlers = new HashMap<Class<?>, Method> ();
        m_ownedWorkerClassNamesCadinalityMap = new HashMap<String, Integer> ();
        m_ownedWorkerClassNamesPriorityMap = new HashMap<String, WaveWorkerPriority> ();
        m_ownedEventClasses = new HashSet<String> ();
        m_waveLinearSequencerSteps = new HashMap<String, Method> ();
        m_waveSynchronousLinearSequencerSteps = new HashMap<String, Method> ();
        m_waveMessageCallbacks = new HashMap<String, Method> ();
        m_waveTimerExpirationHandlers = new HashMap<String, Method> ();
        m_waveEventHandlers = new HashMap<String, Method> ();
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
                if ((superInterfaceName.startsWith ("java.")) || (superInterfaceName.startsWith ("javax.")))
                {
                    continue;
                }

                final WaveJavaInterface waveJavaSuperInterface = WaveJavaSourceRepository.getWaveJavaInterface (superInterfaceName);

                WaveAssertUtils.waveAssert (null != waveJavaSuperInterface);

                m_superInterfaces.put (superInterfaceName, waveJavaSuperInterface);

                waveJavaSuperInterface.addChildClass (this);
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

    private void addChildClass (final WaveJavaClass childClass)
    {
        WaveAssertUtils.waveAssert (null != childClass);

        m_childClasses.put (childClass.getName (), childClass);
    }

    public void setSuperClass (final String superClassName)
    {
        if ((superClassName.startsWith ("java.")) || (superClassName.startsWith ("javax.")))
        {
            return;
        }

        if (WaveStringUtils.isNotBlank (superClassName))
        {
            final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (superClassName);

            if (null == waveJavaClass)
            {
                WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN, "Could not find super class : " + superClassName, true, false);
            }
            else
            {
                m_superClass = waveJavaClass;

                m_superClass.addChildClass (this);
            }
        }
    }

    public String getSuperClassName ()
    {
        String superClassName = null;

        if (null != m_superClass)
        {
            superClassName = m_superClass.getName ();
        }

        return (superClassName);
    }

    private void addAnonymousClass (final WaveJavaClass anonymousClass)
    {
        WaveAssertUtils.waveAssert (null != anonymousClass);

        m_anonymousClasses.put (anonymousClass.getName (), anonymousClass);

    }

    public void setDeclaringClass (final String declaringClassName)
    {
        if (WaveStringUtils.isNotBlank (declaringClassName))
        {
            final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (declaringClassName);

            WaveAssertUtils.waveAssert (null != waveJavaClass);

            m_declaringClass = waveJavaClass;

            m_declaringClass.addAnonymousClass (this);
        }
    }

    public String getTypeName ()
    {
        return (m_typeName);
    }

    @Override
    public void computeStage1 ()
    {
        Class<?> reflectionClass = null;

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "Computing for Java Class (Stage 1) " + m_name, true, false);

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

        final Class<?> reflectionSuperClass = reflectionClass.getSuperclass ();

        final String reflectionSuperClassName = reflectionSuperClass.getName ();

        WaveTraceUtils.infoTracePrintf ("    Super Class : %s", reflectionSuperClassName);

        if (reflectionSuperClassName.equals (WaveMessage.class.getName ()))
        {
            WaveTraceUtils.infoTracePrintf ("    Found Message as Super Class for : %s", m_name);
        }

        setSuperClass (reflectionSuperClassName);

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

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "    Computing Serialization Reflection AttributesMap For Declared Fields for Java Class " + m_name, true, false);

        computeSerializationReflectionAttributesMapForDeclaredFields (reflectionClass);
    }

    @Override
    public void computeStage2 ()
    {
        Class<?> reflectionClass = null;

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "Computing for Java Class (stage 2) " + m_name, true, false);

        try
        {
            reflectionClass = Class.forName (m_name);
        }
        catch (final ClassNotFoundException e)
        {
            e.printStackTrace ();
            WaveAssertUtils.waveAssert ();
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "    Computing Message Handlers for Java Class " + m_name, true, false);

        computeMessageHandlers (reflectionClass);

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "    Computing Workers for Java Class " + m_name, true, false);

        computeWorkers (reflectionClass);

        computeSequencerSteps (reflectionClass);

        computeWaveMessageCallbacks (reflectionClass);

        computeWaveTimerExpirationHandlers (reflectionClass);

        computeWaveEventHandlers (reflectionClass);

        computeSupportedEvents (reflectionClass);

        computeShellCommandHandlers (reflectionClass);

        computeShellSubordinates (reflectionClass);

        computeShellRoot (reflectionClass);
    }

    private void computeSerializationReflectionAttributesMapForDeclaredFields (final Class<?> reflectionClass)
    {
        if (!(isADerivativeOfSerializableObject ()))
        {
            return;
        }

        final Annotation annotationForNonSerializable = reflectionClass.getAnnotation (NonSerializable.class);

        if (null != annotationForNonSerializable)
        {
            final NonSerializable nonSerializable = (NonSerializable) (annotationForNonSerializable);

            WaveAssertUtils.waveAssert (null != nonSerializable);

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Ignoring %s from Serialization computations since it is annotated with @NonSerializable", reflectionClass.getName ());

            return;
        }

        final Field[] declaredFields = reflectionClass.getDeclaredFields ();

        if (null != declaredFields)
        {
            Field.setAccessible (declaredFields, true);
        }
        else
        {
            return;
        }

        for (final Field declaredField : declaredFields)
        {
            WaveAssertUtils.waveAssert (null != declaredField);

            if (0 != ((declaredField.getModifiers ()) & (Modifier.STATIC)))
            {
                continue;
            }

            Annotation annotation = null;

            annotation = declaredField.getAnnotation (NonSerializable.class);

            if (null != annotation)
            {
                continue;
            }

            final String declaredFieldName = declaredField.getName ();
            String xmlWaveXPathPath = null;
            String serializableAttributeName = null;
            boolean serializableAttributeIsPrimary = false;
            boolean serializableAttributeIsOperational = false;
            UI32 serializableAttributeUserTag = new UI32 (0);

            if (WaveStringUtils.isNotBlank (declaredFieldName))
            {
                serializableAttributeName = declaredFieldName.replaceFirst ("^m_", "");
            }
            else
            {
                WaveAssertUtils.waveAssert ();
            }

            annotation = declaredField.getAnnotation (XmlWaveXPath.class);

            if (null != annotation)
            {
                final XmlWaveXPath xmlWaveXPath = (XmlWaveXPath) (annotation);

                WaveAssertUtils.waveAssert (null != xmlWaveXPath);

                xmlWaveXPathPath = xmlWaveXPath.path ();
            }

            annotation = declaredField.getAnnotation (SerializableAttribute.class);

            if (null != annotation)
            {
                final SerializableAttribute serializableAttribute = (SerializableAttribute) (annotation);

                WaveAssertUtils.waveAssert (null != serializableAttribute);

                if (WaveStringUtils.isNotBlank (serializableAttribute.name ()))
                {
                    serializableAttributeName = (serializableAttribute.name ()).replaceFirst ("^m_", "");
                }

                xmlWaveXPathPath = serializableAttribute.xmlWaveXPath ();
                serializableAttributeIsPrimary = serializableAttribute.isPrimary ();
                serializableAttributeIsOperational = serializableAttribute.isOperational ();
                serializableAttributeUserTag = new UI32 (serializableAttribute.userTag ());
            }

            WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (serializableAttributeName));

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "    Adding Reflection Attribute : %s", serializableAttributeName);

            final ReflectionAttribute reflectionAttribute = new ReflectionAttribute ();

            WaveAssertUtils.waveAssert (null != reflectionAttribute);

            reflectionAttribute.setAttributeName (serializableAttributeName);
            reflectionAttribute.setAttributeFieldName (declaredFieldName);
            reflectionAttribute.setField (declaredField);
            reflectionAttribute.setAttributeUserTag (serializableAttributeUserTag);

            m_serializationReflectionAttributesMapForDeclaredFields.addAttribute (reflectionAttribute);
        }
    }

    private void computeMessageHandlers (final Class<?> reflectionClass)
    {
        if ((!(isADerivativeOfWaveObjectManager ())) && (!(isADerivativeOfWaveWorker ())) && (!(isADerivativeOfWaveManagedObject ())) && (!(waveObjectManagerIsADerivativeOf (m_typeName))) && (!(waveWorkerIsADerivativeOf (m_typeName))) && (!(waveManagedObjectIsADerivativeOf (m_typeName))))
        {
            return;
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Computing Message Handlers for Java Class " + m_name, true, false);

        final Method[] declaredMethods = reflectionClass.getDeclaredMethods ();

        for (final Method declaredMethod : declaredMethods)
        {
            WaveAssertUtils.waveAssert (null != declaredMethod);

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Considering Method " + declaredMethod.toString (), true, false);

            final Annotation annotationForNonMessageHandler = declaredMethod.getAnnotation (NonMessageHandler.class);

            if (null != annotationForNonMessageHandler)
            {
                final NonMessageHandler nonMessageHandler = (NonMessageHandler) annotationForNonMessageHandler;

                WaveAssertUtils.waveAssert (null != nonMessageHandler);

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeMessageHandlers : Ignoring %s : %s from Message Handler computations since it is annotated with @NonMessageHandler", m_typeName, declaredMethod.toString ());

                continue;
            }

            final int numberOfParameters = declaredMethod.getParameterCount ();

            if (1 == numberOfParameters)
            {
                final Class<?>[] parameterTypes = declaredMethod.getParameterTypes ();

                final String parameterClassTypeName = parameterTypes[0].getTypeName ();

                final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (parameterClassTypeName);

                if (null != waveJavaClass)
                {
                    if ((waveJavaClass.isADerivativeOfWaveMessage ()) && (!(waveJavaClass.isADerivativeOfWaveEvent ())))
                    {
                        if (m_messageHandlers.containsKey (parameterTypes[0]))
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeMessageHandlers : Trying to add a message Handler for Class %s with Message Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeMessageHandlers : Already persent Message Handler method : %s", (m_messageHandlers.get (parameterTypes[0])).toString ());
                            WaveAssertUtils.waveAssert ();
                        }
                        else
                        {
                            declaredMethod.setAccessible (true);

                            final Class<?> waveMessageClass = parameterTypes[0];

                            WaveAssertUtils.waveAssert (null != waveMessageClass);

                            m_messageHandlers.put (waveMessageClass, declaredMethod);

                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeMessageHandlers : Added a Message Handler for Class %s with Message Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                        }
                    }
                }
            }
        }
    }

    private void computeWorkers (final Class<?> reflectionClass)
    {
        if (!(isADerivativeOfWaveWorker ()))
        {
            return;
        }

        WaveJavaClass waveJavaClassForOwnerOm = null;
        int cardinality = 1;
        WaveWorkerPriority priority = WaveWorkerPriority.WAVE_WORKER_PRIORITY_0;

        final Annotation annotationForOwnerOM = reflectionClass.getAnnotation (OwnerOM.class);

        if (null != annotationForOwnerOM)
        {
            final OwnerOM ownerOM = (OwnerOM) annotationForOwnerOM;

            WaveAssertUtils.waveAssert (null != ownerOM);

            final Class<?> ownerOmClass = ownerOM.om ();

            WaveAssertUtils.waveAssert (null != ownerOmClass);

            final String ownerOmClassName = ownerOmClass.getName ();

            if (WaveStringUtils.isNotBlank (ownerOmClassName))
            {
                waveJavaClassForOwnerOm = WaveJavaSourceRepository.getWaveJavaClass (ownerOmClassName);

                WaveAssertUtils.waveAssert (null != waveJavaClassForOwnerOm);
            }
        }

        final Annotation annotationForCardinality = reflectionClass.getAnnotation (Cardinality.class);

        if (null != annotationForCardinality)
        {
            final Cardinality cardinalityAnnotation = (Cardinality) annotationForCardinality;

            WaveAssertUtils.waveAssert (null != cardinalityAnnotation);

            cardinality = cardinalityAnnotation.value ();

            WaveAssertUtils.waveAssert (0 != cardinality);
        }

        final Annotation annotationForPriority = reflectionClass.getAnnotation (WorkerPriority.class);

        if (null != annotationForPriority)
        {
            final WorkerPriority priorityAnnotation = (WorkerPriority) annotationForPriority;

            WaveAssertUtils.waveAssert (null != priorityAnnotation);

            priority = priorityAnnotation.value ();
        }

        if (null != waveJavaClassForOwnerOm)
        {
            waveJavaClassForOwnerOm.addOwnedWorker (reflectionClass.getName (), cardinality, priority);
        }
    }

    private void computeSequencerSteps (final Class<?> reflectionClass)
    {
        if ((!(isADerivativeOfWaveObjectManager ())) && (!(isADerivativeOfWaveWorker ())) && (!(isADerivativeOfWaveManagedObject ())) && (!(waveObjectManagerIsADerivativeOf (m_typeName))) && (!(waveWorkerIsADerivativeOf (m_typeName))) && (!(waveManagedObjectIsADerivativeOf (m_typeName))))
        {
            return;
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Computing Sequencer Steps for Java Class " + m_name, true, false);

        final Method[] declaredMethods = reflectionClass.getDeclaredMethods ();

        for (final Method declaredMethod : declaredMethods)
        {
            WaveAssertUtils.waveAssert (null != declaredMethod);

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Considering Method " + declaredMethod.toString (), true, false);

            final Annotation annotationForNonSeqeuncerStep = declaredMethod.getAnnotation (NonSequencerStep.class);

            if (null != annotationForNonSeqeuncerStep)
            {
                final NonSequencerStep nonSequencerStep = (NonSequencerStep) annotationForNonSeqeuncerStep;

                WaveAssertUtils.waveAssert (null != nonSequencerStep);

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeSequencerSteps : Ignoring %s : %s from Sequencer Step computations since it is annotated with @NonSequencerStep", m_typeName, declaredMethod.toString ());

                continue;
            }

            final int numberOfParameters = declaredMethod.getParameterCount ();

            if (1 == numberOfParameters)
            {
                final Class<?>[] parameterTypes = declaredMethod.getParameterTypes ();

                final String parameterClassTypeName = parameterTypes[0].getTypeName ();

                final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (parameterClassTypeName);

                if (null != waveJavaClass)
                {
                    if (waveJavaClass.isADerivativeOfWaveLinearSequencerContext ())
                    {
                        if (m_waveLinearSequencerSteps.containsKey (declaredMethod.getName ()))
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeSequencerSteps : Trying to add a Sequencer Step for Class %s with WaveLinearSequencer Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeSequencerSteps : Already persent Sequencer Step method : %s", (m_waveLinearSequencerSteps.get (declaredMethod.getName ())).toString ());
                            WaveAssertUtils.waveAssert ();
                        }
                        else
                        {
                            declaredMethod.setAccessible (true);

                            m_waveLinearSequencerSteps.put (declaredMethod.getName (), declaredMethod);

                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeSequencerSteps : Added a Sequencer Step for Class %s with Wave Linear Sequencer Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                        }
                    }
                    else if (waveJavaClass.isADerivativeOfWaveSynchronousLinearSequencerContext ())
                    {
                        if (m_waveSynchronousLinearSequencerSteps.containsKey (declaredMethod.getName ()))
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeSequencerSteps : Trying to add a Synchronous Sequencer Step for Class %s with WaveSynchronousLinearSequencer Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeSequencerSteps : Already persent Synchronous Sequencer Step method : %s", (m_waveSynchronousLinearSequencerSteps.get (declaredMethod.getName ())).toString ());
                            WaveAssertUtils.waveAssert ();
                        }
                        else
                        {
                            declaredMethod.setAccessible (true);

                            m_waveSynchronousLinearSequencerSteps.put (declaredMethod.getName (), declaredMethod);

                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeSequencerSteps : Added a Synchronous Sequencer Step for Class %s with Wave Synchronous Linear Sequencer Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                        }
                    }
                }
            }
        }
    }

    private void computeWaveMessageCallbacks (final Class<?> reflectionClass)
    {
        if ((!(isADerivativeOfWaveObjectManager ())) && (!(isADerivativeOfWaveWorker ())) && (!(isADerivativeOfWaveManagedObject ())) && (!(waveObjectManagerIsADerivativeOf (m_typeName))) && (!(waveWorkerIsADerivativeOf (m_typeName))) && (!(waveManagedObjectIsADerivativeOf (m_typeName))))
        {
            return;
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Wave Message Callbacks for Java Class " + m_name, true, false);

        final Method[] declaredMethods = reflectionClass.getDeclaredMethods ();

        for (final Method declaredMethod : declaredMethods)
        {
            WaveAssertUtils.waveAssert (null != declaredMethod);

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Considering Method " + declaredMethod.toString (), true, false);

            final Annotation annotationForNonMessageCallback = declaredMethod.getAnnotation (NonMessageCallback.class);

            if (null != annotationForNonMessageCallback)
            {
                final NonMessageCallback nonMessageCallback = (NonMessageCallback) annotationForNonMessageCallback;

                WaveAssertUtils.waveAssert (null != nonMessageCallback);

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveMessageCallbacks : Ignoring %s : %s from Message Callback computations since it is annotated with @NonMessageCallback", m_typeName, declaredMethod.toString ());

                continue;
            }

            final int numberOfParameters = declaredMethod.getParameterCount ();

            if (3 == numberOfParameters)
            {
                final Class<?>[] parameterTypes = declaredMethod.getParameterTypes ();

                final String parameterClassTypeName0 = parameterTypes[0].getTypeName ();

                if (!(parameterClassTypeName0.equals (FrameworkStatus.class.getTypeName ())))
                {
                    continue;
                }

                final String parameterClassTypeName2 = parameterTypes[2].getTypeName ();

                Class<?> classForParameter2 = null;

                try
                {
                    classForParameter2 = Class.forName (parameterClassTypeName2);
                }
                catch (final ClassNotFoundException e)
                {
                    WaveTraceUtils.errorTracePrintf ("WaveJavaClass.computeWaveMessageCallbacks : %s class could not be found and hence skipping %s", parameterClassTypeName2, declaredMethod.getName ());

                    continue;
                }

                if (null == classForParameter2)
                {
                    continue;
                }

                if (!(Object.class.isAssignableFrom (classForParameter2)))
                {
                    continue;
                }

                final String parameterClassTypeName1 = parameterTypes[1].getTypeName ();

                final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (parameterClassTypeName1);

                if (null != waveJavaClass)
                {
                    if (waveJavaClass.isADerivativeOfWaveMessage ())
                    {
                        if (m_waveMessageCallbacks.containsKey (declaredMethod.getName ()))
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveMessageCallbacks : Trying to add a Mesage Callback for Class %s with Message Type %s, handler method : %s", m_typeName, parameterClassTypeName1, declaredMethod.getName ());
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveMessageCallbacks : Already persent Message Callback method : %s", (m_waveMessageCallbacks.get (declaredMethod.getName ())).toString ());
                            WaveAssertUtils.waveAssert ();
                        }
                        else
                        {
                            declaredMethod.setAccessible (true);

                            m_waveMessageCallbacks.put (declaredMethod.getName (), declaredMethod);

                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveMessageCallbacks : Added a Message Callback for Class %s with Wave Message Type %s, handler method : %s", m_typeName, parameterClassTypeName1, declaredMethod.getName ());
                        }
                    }
                }
            }
        }
    }

    private void computeWaveTimerExpirationHandlers (final Class<?> reflectionClass)
    {
        if ((!(isADerivativeOfWaveObjectManager ())) && (!(isADerivativeOfWaveWorker ())) && (!(isADerivativeOfWaveManagedObject ())) && (!(waveObjectManagerIsADerivativeOf (m_typeName))) && (!(waveWorkerIsADerivativeOf (m_typeName))) && (!(waveManagedObjectIsADerivativeOf (m_typeName))))
        {
            return;
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Computing Timer Expiration Handlers for Java Class " + m_name, true, false);

        final Method[] declaredMethods = reflectionClass.getDeclaredMethods ();

        for (final Method declaredMethod : declaredMethods)
        {
            WaveAssertUtils.waveAssert (null != declaredMethod);

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Considering Method " + declaredMethod.toString (), true, false);

            final Annotation annotationForNonTimerExpirationHandler = declaredMethod.getAnnotation (NonTimerExpirationHandler.class);

            if (null != annotationForNonTimerExpirationHandler)
            {
                final NonTimerExpirationHandler nonTimerExpirationHandler = (NonTimerExpirationHandler) annotationForNonTimerExpirationHandler;

                WaveAssertUtils.waveAssert (null != nonTimerExpirationHandler);

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveTimerExpirationHandlers : Ignoring %s : %s from Timer Expiration Handler computations since it is annotated with @NonTimerExpirationHandler", m_typeName, declaredMethod.toString ());

                continue;
            }

            final int numberOfParameters = declaredMethod.getParameterCount ();

            if (2 == numberOfParameters)
            {
                final Class<?>[] parameterTypes = declaredMethod.getParameterTypes ();

                final String parameterClassTypeName1 = parameterTypes[1].getTypeName ();

                Class<?> classForParameter1 = null;

                try
                {
                    classForParameter1 = Class.forName (parameterClassTypeName1);
                }
                catch (final ClassNotFoundException e)
                {
                    WaveTraceUtils.errorTracePrintf ("WaveJavaClass.computeWaveTimerExpirationHandlers : %s class could not be found and hence skipping %s", parameterClassTypeName1, declaredMethod.getName ());

                    continue;
                }

                if (null == classForParameter1)
                {
                    continue;
                }

                if (!(Object.class.isAssignableFrom (classForParameter1)))
                {
                    continue;
                }

                final String parameterClassTypeName = parameterTypes[0].getTypeName ();

                final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (parameterClassTypeName);

                if (null != waveJavaClass)
                {
                    if (waveJavaClass.isADerivativeOfTimerHandle ())
                    {
                        if (m_waveTimerExpirationHandlers.containsKey (declaredMethod.getName ()))
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveTimerExpirationHandlers : Trying to add a Timer Expiration Handler for Class %s with TimerHandle Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveTimerExpirationHandlers : Already persent Timer Expiration Handler method : %s", (m_waveTimerExpirationHandlers.get (declaredMethod.getName ())).toString ());
                            WaveAssertUtils.waveAssert ();
                        }
                        else
                        {
                            declaredMethod.setAccessible (true);

                            m_waveTimerExpirationHandlers.put (declaredMethod.getName (), declaredMethod);

                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveTimerExpirationHandlers : Added a Timer Expiration Handler for Class %s with Wave Linear Sequencer Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                        }
                    }
                }
            }
        }
    }

    private void computeWaveEventHandlers (final Class<?> reflectionClass)
    {
        if ((!(isADerivativeOfWaveObjectManager ())) && (!(isADerivativeOfWaveWorker ())) && (!(isADerivativeOfWaveManagedObject ())) && (!(waveObjectManagerIsADerivativeOf (m_typeName))) && (!(waveWorkerIsADerivativeOf (m_typeName))) && (!(waveManagedObjectIsADerivativeOf (m_typeName))))
        {
            return;
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Computing Event Handlers for Java Class " + m_name, true, false);

        final Method[] declaredMethods = reflectionClass.getDeclaredMethods ();

        for (final Method declaredMethod : declaredMethods)
        {
            WaveAssertUtils.waveAssert (null != declaredMethod);

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Considering Method " + declaredMethod.toString (), true, false);

            final Annotation annotationForNonEventHandler = declaredMethod.getAnnotation (NonEventHandler.class);

            if (null != annotationForNonEventHandler)
            {
                final NonEventHandler nonEventHandler = (NonEventHandler) annotationForNonEventHandler;

                WaveAssertUtils.waveAssert (null != nonEventHandler);

                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveEventHandlers : Ignoring %s : %s from Event Handler computations since it is annotated with @NonEventHandler", m_typeName, declaredMethod.toString ());

                continue;
            }

            final int numberOfParameters = declaredMethod.getParameterCount ();

            if (1 == numberOfParameters)
            {
                final Class<?>[] parameterTypes = declaredMethod.getParameterTypes ();

                final String parameterClassTypeName = parameterTypes[0].getTypeName ();

                final WaveJavaClass waveJavaClass = WaveJavaSourceRepository.getWaveJavaClass (parameterClassTypeName);

                if (null != waveJavaClass)
                {
                    if (waveJavaClass.isADerivativeOfWaveEvent ())
                    {
                        if (m_waveEventHandlers.containsKey (declaredMethod.getName ()))
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveEventHandlers : Trying to add a Event Handler for Class %s with Event Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveEventHandlers : Already persent Event Handler method : %s", (m_waveEventHandlers.get (declaredMethod.getName ())).toString ());
                            WaveAssertUtils.waveAssert ();
                        }
                        else
                        {
                            declaredMethod.setAccessible (true);

                            final Class<?> waveEventClass = parameterTypes[0];

                            m_waveEventHandlers.put (declaredMethod.getName (), declaredMethod);
                            m_eventHandlers.put (waveEventClass, declaredMethod);

                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeWaveEventHandlers : Added a Event Handler for Class %s with Event Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
                        }
                    }
                }
            }
        }
    }

    private void computeSupportedEvents (final Class<?> reflectionClass)
    {
        if (!(isADerivativeOfWaveEvent ()))
        {
            return;
        }

        WaveJavaClass waveJavaClassForOwnerOm = null;

        final Annotation annotationForOwnerOM = reflectionClass.getAnnotation (OwnerOM.class);

        if (null != annotationForOwnerOM)
        {
            final OwnerOM ownerOM = (OwnerOM) annotationForOwnerOM;

            WaveAssertUtils.waveAssert (null != ownerOM);

            final Class<?> ownerOmClass = ownerOM.om ();

            WaveAssertUtils.waveAssert (null != ownerOmClass);

            final String ownerOmClassName = ownerOmClass.getName ();

            if (WaveStringUtils.isNotBlank (ownerOmClassName))
            {
                waveJavaClassForOwnerOm = WaveJavaSourceRepository.getWaveJavaClass (ownerOmClassName);

                WaveAssertUtils.waveAssert (null != waveJavaClassForOwnerOm);

                waveJavaClassForOwnerOm.addOwnedEvent (reflectionClass.getName ());
            }
        }
    }

    private boolean isAKnownWorker (final String workerClassName)
    {
        if (m_ownedWorkerClassNamesCadinalityMap.containsKey (workerClassName))
        {
            return (true);
        }
        else
        {
            if (null != m_superClass)
            {
                return (m_superClass.isAKnownWorker (workerClassName));
            }
            else
            {
                return (false);
            }
        }
    }

    private boolean validateWorker (final String workerClassName)
    {
        final boolean isKnown1 = m_ownedWorkerClassNamesCadinalityMap.containsKey (workerClassName);
        final boolean isKnown2 = m_ownedWorkerClassNamesPriorityMap.containsKey (workerClassName);

        if (isKnown1 == isKnown2)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    private boolean validateWorkerClassEntries ()
    {
        for (final String workerClassName : m_ownedWorkerClassNamesCadinalityMap.keySet ())
        {
            if (!(m_ownedWorkerClassNamesPriorityMap.containsKey (workerClassName)))
            {
                return (false);
            }
        }

        if (null != m_superClass)
        {
            return (m_superClass.validateWorkerClassEntries ());
        }
        else
        {
            return (true);
        }
    }

    private void addOwnedWorker (final String workerClassName, final int cardinality, final WaveWorkerPriority priority)
    {
        if (isAKnownWorker (workerClassName))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.addOwnedWorker : %s is already a known worker class name.", workerClassName);

            WaveAssertUtils.waveAssert ();
        }

        if (!(validateWorker (workerClassName)))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.addOwnedWorker : %s validation failed.", workerClassName);

            WaveAssertUtils.waveAssert ();
        }

        m_ownedWorkerClassNamesCadinalityMap.put (workerClassName, cardinality);
        m_ownedWorkerClassNamesPriorityMap.put (workerClassName, priority);

        WaveTraceUtils.infoTracePrintf ("    Successfully added %s worker to %s", workerClassName, m_name);
    }

    private boolean isAKnownEvent (final String eventClassName)
    {
        if (m_ownedEventClasses.contains (eventClassName))
        {
            return (true);
        }
        else
        {
            if (null != m_superClass)
            {
                return (m_superClass.isAKnownEvent (eventClassName));
            }
            else
            {
                return (false);
            }
        }
    }

    private void addOwnedEvent (final String eventClassName)
    {
        if (isAKnownEvent (eventClassName))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.addOwnedEvent : %s is already a known event class name.", eventClassName);

            WaveAssertUtils.waveAssert ();

            return;
        }

        m_ownedEventClasses.add (eventClassName);

        WaveTraceUtils.infoTracePrintf ("    Successfully added %s event to %s", eventClassName, m_name);
    }

    public Set<String> getAllDescendants ()
    {
        final Set<String> allDescendantsSet = new HashSet<String> ();

        for (final Map.Entry<String, WaveJavaClass> descendant : m_childClasses.entrySet ())
        {
            allDescendantsSet.add (descendant.getKey ());

            allDescendantsSet.addAll ((descendant.getValue ()).getAllDescendants ());
        }

        return (allDescendantsSet);
    }

    public Set<String> getAllDescendantsTypeNames ()
    {
        final Set<String> allDescendantsTypeNamesSet = new HashSet<String> ();

        for (final Map.Entry<String, WaveJavaClass> descendant : m_childClasses.entrySet ())
        {
            allDescendantsTypeNamesSet.add ((descendant.getValue ()).getTypeName ());

            allDescendantsTypeNamesSet.addAll ((descendant.getValue ()).getAllDescendantsTypeNames ());
        }

        return (allDescendantsTypeNamesSet);
    }

    public boolean isAnnotatedWith (final String annotationName)
    {
        return (m_annotations.containsKey (annotationName));
    }

    public ReflectionAttributesMap getSerializationReflectionAttributesMapForDeclaredFields ()
    {
        return (m_serializationReflectionAttributesMapForDeclaredFields);
    }

    public boolean isADerivativeOfSerializableObject ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (SerializableObject.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfWaveObjectManager ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (WaveObjectManager.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean waveObjectManagerIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (WaveObjectManager.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfWaveMessage ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (WaveMessage.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean waveMessageIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (WaveMessage.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfWaveWorker ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (WaveWorker.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean waveWorkerIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (WaveWorker.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfWaveManagedObject ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (WaveManagedObject.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean waveManagedObjectIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (WaveManagedObject.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfWaveLinearSequencerContext ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (WaveLinearSequencerContext.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean waveLinearSequencerContextIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (WaveLinearSequencerContext.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfWaveSynchronousLinearSequencerContext ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (WaveSynchronousLinearSequencerContext.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean waveSynchronousLinearSequencerContextIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (WaveSynchronousLinearSequencerContext.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfTimerHandle ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (TimerHandle.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean timerHandleIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (TimerHandle.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfWaveEvent ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (WaveEvent.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean waveEventIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (WaveEvent.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    public boolean isADerivativeOfShellBase ()
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (m_name);

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (ShellBase.class.getName ()))
            {
                return (true);
            }
        }

        return (false);
    }

    public static boolean shellBaseIsADerivativeOf (final String derivedFromClassName)
    {
        final Vector<String> inheritanceHierarchy = WaveJavaSourceRepository.getInheritanceHeirarchyForClassLatestFirstIncludingSelf (ShellBase.class.getName ());

        for (final String className : inheritanceHierarchy.toArray (new String[0]))
        {
            if (WaveStringUtils.isBlank (className))
            {
                break;
            }
            else if (className.equals (derivedFromClassName))
            {
                return (true);
            }
        }

        return (false);
    }

    private void getAttributesMapForInheritanceHierarchy (final AttributesMap attributesMap)
    {
        WaveAssertUtils.waveAssert (null != attributesMap);

        if (null != m_superClass)
        {
            m_superClass.getAttributesMapForInheritanceHierarchy (attributesMap);
        }

        m_serializationReflectionAttributesMapForDeclaredFields.addCorrespondingAttributesToAttributesMap (attributesMap);
    }

    public AttributesMap getAttributesMapForInheritanceHierarchy ()
    {
        final AttributesMap attributesMap = new AttributesMap ();

        WaveAssertUtils.waveAssert (null != attributesMap);

        getAttributesMapForInheritanceHierarchy (attributesMap);

        return (attributesMap);
    }

    private void getMessageHandlersInInheritanceHierarchyPreferringLatest (final Map<Class<?>, Method> messageHandlersInInheritanceHierarchyPreferringLatest)
    {
        WaveAssertUtils.waveAssert (null != messageHandlersInInheritanceHierarchyPreferringLatest);

        for (final Map.Entry<Class<?>, Method> entry : m_messageHandlers.entrySet ())
        {
            final Method alreadyExistingMethod = messageHandlersInInheritanceHierarchyPreferringLatest.putIfAbsent (entry.getKey (), entry.getValue ());

            WaveAssertUtils.waveAssert (null == alreadyExistingMethod);
        }

        if (null != m_superClass)
        {
            m_superClass.getMessageHandlersInInheritanceHierarchyPreferringLatest (messageHandlersInInheritanceHierarchyPreferringLatest);
        }
    }

    public Map<Class<?>, Method> getMessageHandlersInInheritanceHierarchyPreferringLatest ()
    {
        final Map<Class<?>, Method> messageHandlersInInheritanceHierarchyPreferringLatest = new HashMap<Class<?>, Method> ();

        WaveAssertUtils.waveAssert (null != messageHandlersInInheritanceHierarchyPreferringLatest);

        getMessageHandlersInInheritanceHierarchyPreferringLatest (messageHandlersInInheritanceHierarchyPreferringLatest);

        return (messageHandlersInInheritanceHierarchyPreferringLatest);
    }

    private void getEventHandlersInInheritanceHierarchyPreferringLatest (final Map<Class<?>, Method> eventHandlersInInheritanceHierarchyPreferringLatest)
    {
        WaveAssertUtils.waveAssert (null != eventHandlersInInheritanceHierarchyPreferringLatest);

        for (final Map.Entry<Class<?>, Method> entry : m_eventHandlers.entrySet ())
        {
            final Method alreadyExistingMethod = eventHandlersInInheritanceHierarchyPreferringLatest.putIfAbsent (entry.getKey (), entry.getValue ());

            WaveAssertUtils.waveAssert (null == alreadyExistingMethod);
        }

        if (null != m_superClass)
        {
            m_superClass.getEventHandlersInInheritanceHierarchyPreferringLatest (eventHandlersInInheritanceHierarchyPreferringLatest);
        }
    }

    public Map<Class<?>, Method> getEventHandlersInInheritanceHierarchyPreferringLatest ()
    {
        final Map<Class<?>, Method> eventHandlersInInheritanceHierarchyPreferringLatest = new HashMap<Class<?>, Method> ();

        WaveAssertUtils.waveAssert (null != eventHandlersInInheritanceHierarchyPreferringLatest);

        getEventHandlersInInheritanceHierarchyPreferringLatest (eventHandlersInInheritanceHierarchyPreferringLatest);

        return (eventHandlersInInheritanceHierarchyPreferringLatest);
    }

    public Vector<String> getWorkerClassNames ()
    {
        final Vector<String> workerClassNames = new Vector<String> ();

        if (!(validateWorkerClassEntries ()))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.getWorkerClassNames : validation failed.");

            WaveAssertUtils.waveAssert ();
        }

        for (final String workerClassName : m_ownedWorkerClassNamesCadinalityMap.keySet ())
        {
            workerClassNames.add (workerClassName);
        }

        if (null != m_superClass)
        {
            final Vector<String> workerClassNamesFromImmediteBaseClass = m_superClass.getWorkerClassNames ();

            if (null != workerClassNamesFromImmediteBaseClass)
            {
                workerClassNames.addAll (workerClassNamesFromImmediteBaseClass);
            }
        }

        return (workerClassNames);
    }

    public int getWorkerClassCardinality (final String workerClassName)
    {
        if (!(validateWorker (workerClassName)))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.getWorkerClassCardinality : %s validation failed.", workerClassName);

            WaveAssertUtils.waveAssert ();
        }

        if (!(isAKnownWorker (workerClassName)))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.getWorkerClassCardinality : %s is not a known Worker to %s.", workerClassName, m_name);

            WaveAssertUtils.waveAssert ();
        }

        if (m_ownedWorkerClassNamesCadinalityMap.containsKey (workerClassName))
        {
            return (m_ownedWorkerClassNamesCadinalityMap.get (workerClassName));
        }
        else
        {
            if (null != m_superClass)
            {
                return (m_superClass.getWorkerClassCardinality (workerClassName));
            }
            else
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.getWorkerClassCardinality : %s is not a known Worker to %s.  Exhausted seraching the inheritance hierarchy.", workerClassName, m_name);

                WaveAssertUtils.waveAssert ();

                return (0);
            }
        }
    }

    public WaveWorkerPriority getWorkerClassPriority (final String workerClassName)
    {
        if (!(validateWorker (workerClassName)))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.WaveWorkerPriority : %s validation failed.", workerClassName);

            WaveAssertUtils.waveAssert ();
        }

        if (!(isAKnownWorker (workerClassName)))
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.WaveWorkerPriority : %s is not a known Worker to %s.", workerClassName, m_name);

            WaveAssertUtils.waveAssert ();
        }

        if (m_ownedWorkerClassNamesPriorityMap.containsKey (workerClassName))
        {
            return (m_ownedWorkerClassNamesPriorityMap.get (workerClassName));
        }
        else
        {
            if (null != m_superClass)
            {
                return (m_superClass.getWorkerClassPriority (workerClassName));
            }
            else
            {
                WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.getWorkerClassPriority : %s is not a known Worker to %s.  Exhausted seraching the inheritance hierarchy.", workerClassName, m_name);

                WaveAssertUtils.waveAssert ();

                return (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0);
            }
        }
    }

    public void getOwnedEventClassNames (final Set<String> ownedEventClassNames)
    {
        ownedEventClassNames.addAll (m_ownedEventClasses);

        if (null != m_superClass)
        {
            m_superClass.getOwnedEventClassNames (ownedEventClassNames);
        }

    }

    public Set<String> getOwnedEventClassNames ()
    {
        final Set<String> ownedEventClassNames = new HashSet<String> ();

        getOwnedEventClassNames (ownedEventClassNames);

        return (ownedEventClassNames);
    }

    public Method getMethodForWaveLinearSequencerStep (final String waveLinearSequencerStepName)
    {
        final Method method = m_waveLinearSequencerSteps.get (waveLinearSequencerStepName);

        if (null != method)
        {
            return (method);
        }

        if (null != m_superClass)
        {
            return (m_superClass.getMethodForWaveLinearSequencerStep (waveLinearSequencerStepName));
        }
        else
        {
            return (null);
        }
    }

    public Method getMethodForWaveSynchronousLinearSequencerStep (final String waveSynchronousLinearSequencerStepName)
    {
        final Method method = m_waveSynchronousLinearSequencerSteps.get (waveSynchronousLinearSequencerStepName);

        if (null != method)
        {
            return (method);
        }

        if (null != m_superClass)
        {
            return (m_superClass.getMethodForWaveSynchronousLinearSequencerStep (waveSynchronousLinearSequencerStepName));
        }
        else
        {
            return (null);
        }
    }

    public Method getMethodForWaveMessageCallback (final String waveMessageCallbackName)
    {
        final Method method = m_waveMessageCallbacks.get (waveMessageCallbackName);

        if (null != method)
        {
            return (method);
        }

        if (null != m_superClass)
        {
            return (m_superClass.getMethodForWaveMessageCallback (waveMessageCallbackName));
        }
        else
        {
            return (null);
        }
    }

    public Method getMethodForWaveTimerExpirationHandler (final String waveTimerExpirationHandlerName)
    {
        final Method method = m_waveTimerExpirationHandlers.get (waveTimerExpirationHandlerName);

        if (null != method)
        {
            return (method);
        }

        if (null != m_superClass)
        {
            return (m_superClass.getMethodForWaveTimerExpirationHandler (waveTimerExpirationHandlerName));
        }
        else
        {
            return (null);
        }
    }

    public Method getMethodForWaveEventHandler (final String waveEventHandlerName)
    {
        final Method method = m_waveEventHandlers.get (waveEventHandlerName);

        if (null != method)
        {
            return (method);
        }

        if (null != m_superClass)
        {
            return (m_superClass.getMethodForWaveEventHandler (waveEventHandlerName));
        }
        else
        {
            return (null);
        }
    }

    private void addShellCommandHandlerMethodForClass (final Class<?> classForShellCommandHandler, final Method methodForShellCommandHandler, final String shellCommand)
    {
        WaveAssertUtils.waveAssert (null != classForShellCommandHandler);
        WaveAssertUtils.waveAssert (null != methodForShellCommandHandler);
        WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (shellCommand));

        Map<String, Method> shellCommandHandlersForClass = s_shellCommandHandlerMethodsByClass.get (classForShellCommandHandler);

        if (null == shellCommandHandlersForClass)
        {
            shellCommandHandlersForClass = new TreeMap<String, Method> ();

            s_shellCommandHandlerMethodsByClass.put (classForShellCommandHandler, shellCommandHandlersForClass);
        }

        final Method shellCommandHandlerMethod = shellCommandHandlersForClass.get (shellCommand);

        if (null == shellCommandHandlerMethod)
        {
            shellCommandHandlersForClass.put (shellCommand, methodForShellCommandHandler);
        }
        else
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.addShellCommandHandlerMethodForClass : %s command is already present for class %s", shellCommand, classForShellCommandHandler.toString ());

            WaveAssertUtils.waveAssert ();
        }
    }

    private void computeShellCommandHandlers (final Class<?> reflectionClass)
    {
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Computing Shell Command Handlers for Java Class " + m_name, true, false);

        final Method[] declaredMethods = reflectionClass.getDeclaredMethods ();

        final Vector<String> temp = new Vector<String> ();
        final String knownClassTypeName = (temp.getClass ()).getTypeName ();

        for (final Method declaredMethod : declaredMethods)
        {
            WaveAssertUtils.waveAssert (null != declaredMethod);

            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Considering Method " + declaredMethod.toString (), true, false);

            final Annotation annotationForShellCommand = declaredMethod.getAnnotation (ShellCommand.class);

            if (null == annotationForShellCommand)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeShellCommandHandlers : Ignoring %s : %s from Shell Command Handler computations since it is not annotated with @ShellCommand", m_typeName, declaredMethod.toString ());

                continue;
            }

            final ShellCommand shellCommand = (ShellCommand) annotationForShellCommand;

            WaveAssertUtils.waveAssert (null != shellCommand);

            final int modifiers = declaredMethod.getModifiers ();

            if (0 == (Modifier.STATIC & modifiers))
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeShellCommandHandlers : Ignoring %s : %s from Shell Command Handler computations since it is not static", m_typeName, declaredMethod.toString ());

                continue;
            }

            final int numberOfParameters = declaredMethod.getParameterCount ();

            if (1 == numberOfParameters)
            {
                final Class<?>[] parameterTypes = declaredMethod.getParameterTypes ();

                final String parameterClassTypeName = parameterTypes[0].getTypeName ();

                if (knownClassTypeName.equals (parameterClassTypeName))
                {
                    final Class<?> classForShellCommandHandler = shellCommand.shell ();

                    String shellCommandToken = shellCommand.token ();

                    if (WaveStringUtils.isBlank (shellCommandToken))
                    {
                        shellCommandToken = declaredMethod.getName ();
                    }

                    addShellCommandHandlerMethodForClass (classForShellCommandHandler, declaredMethod, shellCommandToken);

                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeShellCommandHandlers : Adding a Shell Command Handler for Class %s with argument Type %s, handler method : %s from class %s", classForShellCommandHandler.getTypeName (), parameterClassTypeName, declaredMethod.getName (), m_typeName);
                }
            }
        }
    }

    private void addShellSubordinateForClass (final Class<?> classForShell, final Class<?> classForSubordinate, final String subordinateToken)
    {
        WaveAssertUtils.waveAssert (null != classForShell);
        WaveAssertUtils.waveAssert (null != classForSubordinate);
        WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (subordinateToken));

        Map<String, Class<?>> subordinates = s_shellSubordinatesByClass.get (classForShell);

        if (null == subordinates)
        {
            subordinates = new TreeMap<String, Class<?>> ();

            s_shellSubordinatesByClass.put (classForShell, subordinates);
        }

        final Class<?> existingClassForSubordinate = subordinates.get (subordinateToken);

        if (null == existingClassForSubordinate)
        {
            subordinates.put (subordinateToken, classForSubordinate);
        }
        else
        {
            WaveTraceUtils.fatalTracePrintf ("WaveJavaClass.addShellSubordinateForClass : %s subordinate is already present for class %s", subordinateToken, classForShell.toString ());

            WaveAssertUtils.waveAssert ();
        }
    }

    private void computeShellSubordinates (final Class<?> reflectionClass)
    {
        if (!(isADerivativeOfShellBase ()))
        {
            return;
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Computing Shell Subordinates for Java Class " + m_name, true, false);

        final Annotation annotationForShellSubordinate = reflectionClass.getAnnotation (ShellSubordinate.class);

        if (null == annotationForShellSubordinate)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeShellSubordinates : Ignoring %s from Shell Subordinate computations since it is not annotated with @ShellSubordinate", m_typeName);

            return;
        }

        final ShellSubordinate shellSubordinate = (ShellSubordinate) annotationForShellSubordinate;

        WaveAssertUtils.waveAssert (null != shellSubordinate);

        final Class<?> subordinateParentShellClass = shellSubordinate.shell ();

        WaveAssertUtils.waveAssert (null != subordinateParentShellClass);

        final String subordinateToken = shellSubordinate.token ();

        WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (subordinateToken));

        addShellSubordinateForClass (subordinateParentShellClass, reflectionClass, subordinateToken);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeShellSubordinates : Adding a Shell subordinate for Class : %s, subordinate class : %s", subordinateParentShellClass.getTypeName (), m_typeName);
    }

    public static Map<String, Method> getShellCommandHandlerMethodsForClass (final Class<?> classForShell)
    {
        return (s_shellCommandHandlerMethodsByClass.get (classForShell));
    }

    public static Map<String, Class<?>> getShellSubordinnatesForClass (final Class<?> classForShell)
    {
        return (s_shellSubordinatesByClass.get (classForShell));
    }

    private void computeShellRoot (final Class<?> reflectionClass)
    {
        if (!(isADerivativeOfShellBase ()))
        {
            return;
        }

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "        Proceeding with Computing Shell Sroot for Java Class " + m_name, true, false);

        final Annotation annotationForShellRoot = reflectionClass.getAnnotation (ShellRoot.class);

        if (null == annotationForShellRoot)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeShellRoot : Ignoring %s from Shell Root computations since it is not annotated with @ShellRoot", m_typeName);

            return;
        }

        final ShellRoot shellRoot = (ShellRoot) annotationForShellRoot;

        WaveAssertUtils.waveAssert (null != shellRoot);

        if (null == s_shellRootClass)
        {
            s_shellRootClass = reflectionClass;

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeShellRoot : Set the Shell Root as : %s", m_typeName);
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "WaveJavaClass.computeShellRoot : Shell Root is already set as : %s", s_shellRootClass.getTypeName ());

            WaveAssertUtils.waveAssert ();
        }
    }
}
