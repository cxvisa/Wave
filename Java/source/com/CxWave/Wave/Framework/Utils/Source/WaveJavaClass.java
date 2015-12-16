/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
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
import java.util.Vector;

import com.CxWave.Wave.Framework.Attributes.AttributesMap;
import com.CxWave.Wave.Framework.Attributes.ReflectionAttribute;
import com.CxWave.Wave.Framework.Attributes.ReflectionAttributesMap;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.WaveManagedObject;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Priority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.SerializableAttribute;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveJavaClass extends WaveJavaType
{
    private final String                          m_name;
    private final Map<String, WaveJavaInterface>  m_superInterfaces;
    private final Map<String, WaveJavaAnnotation> m_annotations;
    private WaveJavaClass                         m_superClass;
    private final Map<String, WaveJavaClass>      m_childClasses;
    private final Map<String, WaveJavaClass>      m_anonymousClasses;
    private WaveJavaClass                         m_declaringClass;
    private final ReflectionAttributesMap         m_serializationReflectionAttributesMapForDeclaredFields;
    private String                                m_typeName;
    private final Map<Class<?>, Method>           m_messageHandlers;
    private final Map<String, Integer>            m_ownedWorkerClassNamesCadinalityMap;
    private final Map<String, WaveWorkerPriority> m_ownedWorkerClassNamesPriorityMap;

    public WaveJavaClass (final String name)
    {
        m_name = name;
        m_superInterfaces = new HashMap<String, WaveJavaInterface> ();
        m_annotations = new HashMap<String, WaveJavaAnnotation> ();
        m_childClasses = new HashMap<String, WaveJavaClass> ();
        m_anonymousClasses = new HashMap<String, WaveJavaClass> ();
        m_serializationReflectionAttributesMapForDeclaredFields = new ReflectionAttributesMap ();
        m_messageHandlers = new HashMap<Class<?>, Method> ();
        m_ownedWorkerClassNamesCadinalityMap = new HashMap<String, Integer> ();
        m_ownedWorkerClassNamesPriorityMap = new HashMap<String, WaveWorkerPriority> ();
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
    public void compute ()
    {
        Class<?> reflectionClass = null;

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "Computing for Java Class " + m_name, true, false);

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

        setSuperClass (reflectionSuperClass.getName ());

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

        computeSerializationReflectionAttributesMapForDeclaredFields (reflectionClass);

        computeMessageHandlers (reflectionClass);

        computeWorkers (reflectionClass);
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
        if (!(isADerivativeOfWaveObjectManager ()))
        {
            return;
        }

        final Annotation annotationForNonOM = reflectionClass.getAnnotation (NonOM.class);

        if (null != annotationForNonOM)
        {
            final NonOM nonOM = (NonOM) annotationForNonOM;

            WaveAssertUtils.waveAssert (null != nonOM);

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeMessageHandlers : Ignoring %s from Message Handler computations since it is annotated with @NonOM", reflectionClass.getName ());

            return;
        }

        final Method[] declaredMethods = reflectionClass.getDeclaredMethods ();

        for (final Method declaredMethod : declaredMethods)
        {
            WaveAssertUtils.waveAssert (null != declaredMethod);

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
                    if (waveJavaClass.isADerivativeOfWaveMessage ())
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

                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "WaveJavaClass.computeMessageHandlers : Added a message Handler for Class %s with Message Type %s, handler method : %s", m_typeName, parameterClassTypeName, declaredMethod.getName ());
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

        final Annotation annotationForPriority = reflectionClass.getAnnotation (Priority.class);

        if (null != annotationForPriority)
        {
            final Priority priorityAnnotation = (Priority) annotationForPriority;

            WaveAssertUtils.waveAssert (null != priorityAnnotation);

            priority = priorityAnnotation.value ();
        }

        if (null != waveJavaClassForOwnerOm)
        {
            waveJavaClassForOwnerOm.addOwnedWorker (reflectionClass.getName (), cardinality, priority);
        }
    }

    private void addOwnedWorker (final String workerClassName, final int cardinality, final WaveWorkerPriority priority)
    {
        m_ownedWorkerClassNamesCadinalityMap.put (workerClassName, cardinality);
        m_ownedWorkerClassNamesPriorityMap.put (workerClassName, priority);
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
}
