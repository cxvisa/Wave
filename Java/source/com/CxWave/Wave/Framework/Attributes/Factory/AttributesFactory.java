/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes.Factory;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import com.CxWave.Wave.Framework.Attributes.Attribute;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributesFactory
{
    private static AttributesFactory          s_attributesFactory   = new AttributesFactory ();

    private final Map<String, Constructor<?>> m_constructorsByClass = new HashMap<String, Constructor<?>> ();

    private AttributesFactory ()
    {
    }

    public static AttributesFactory getInstance ()
    {
        if (null == s_attributesFactory)
        {
            s_attributesFactory = new AttributesFactory ();
        }

        WaveAssertUtils.waveAssert (null != s_attributesFactory);

        return (s_attributesFactory);
    }

    private void addSupportedAttributeTypeInternal (final Class<?> attributeClass)
    {
        final Constructor<?>[] declaredConstructors = attributeClass.getDeclaredConstructors ();
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
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not find constructor with 0 arguments for Attribute Type : %s", attributeClass.getName ());
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "    Please declare a constructor with no arguments and retry.");

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            try
            {
                final Method supportedDataTypesMethod = attributeClass.getDeclaredMethod ("getSupportedDataTypes");
            }
            catch (NoSuchMethodException | SecurityException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not find method \"getSupportedDataTypes\" for Attribute Type: %s", attributeClass.getName ());
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "    Please override the method and retry.");

                WaveAssertUtils.waveAssert ();
            }

            try
            {
                constructorWithZeroArguments.setAccessible (true);

                final Object object = constructorWithZeroArguments.newInstance ();

                Attribute attribute = null;

                if (object instanceof Attribute)
                {
                    attribute = (Attribute) object;

                    final Set<String> supportedDataTypes = attribute.getSupportedDataTypes ();

                    for (final String supportedDataType : supportedDataTypes)
                    {
                        if (!(isAKnownSupportedDataType (supportedDataType)))
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "    %s", supportedDataType);

                            m_constructorsByClass.put (supportedDataType, constructorWithZeroArguments);
                        }
                        else
                        {
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Supported Data Type %s claimed by Attribute Type : %s is already supported by %s.  Resulted in a non Attribute Type.", supportedDataType, attributeClass.getName (), (m_constructorsByClass.get (supportedDataType).getName ()));
                            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Duplicate ownership detected for data type : %s", supportedDataType);
                            WaveAssertUtils.waveAssert ();
                        }
                    }
                }
                else
                {
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not create attribute of type : %s in order to check supported data types.  Resulted in a non Attribute Type.", attributeClass.getName ());
                    WaveAssertUtils.waveAssert ();
                }
            }
            catch (InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not create attribute of type : %s", attributeClass.getName ());
                WaveAssertUtils.waveAssert ();
            }
        }
    }

    private boolean isAKnownSupportedDataType (final String dataType)
    {
        return (m_constructorsByClass.containsKey (dataType));
    }

    public static void addSupportedAttributeType (final Class<?> attributeClass)
    {
        (getInstance ()).addSupportedAttributeTypeInternal (attributeClass);
    }

    private Attribute createAttributeInternal (final String attributeTypeName)
    {
        Attribute attribute = null;

        if (m_constructorsByClass.containsKey (attributeTypeName))
        {
            try
            {
                final Object object = (m_constructorsByClass.get (attributeTypeName)).newInstance ();

                if (object instanceof Attribute)
                {
                    attribute = (Attribute) object;
                }
                else
                {
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not create attribute of type : %s.  Resulted in a non Attribute Type.", attributeTypeName);
                    WaveAssertUtils.waveAssert ();
                }
            }
            catch (InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not create attribute of type : %s", attributeTypeName);
                WaveAssertUtils.waveAssert ();
            }
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "%s is not a supported Attribute Type", attributeTypeName);

            WaveAssertUtils.waveAssert ();
        }

        return (attribute);
    }

    public static Attribute createAttribute (final String attributeTypeName)
    {
        return ((getInstance ()).createAttributeInternal (attributeTypeName));
    }
}
