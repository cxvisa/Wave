/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes.Factory;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;

import com.CxWave.Wave.Framework.Attributes.Attribute;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributesFactory
{
    private static AttributesFactory            s_attributesFactory   = new AttributesFactory ();

    private final Map<Class<?>, Constructor<?>> m_constructorsByClass = new HashMap<Class<?>, Constructor<?>> ();

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
            m_constructorsByClass.put (attributeClass, constructorWithZeroArguments);
        }
    }

    public static void addSupportedAttributeType (final Class<?> attributeClass)
    {
        (getInstance ()).addSupportedAttributeTypeInternal (attributeClass);
    }

    private Attribute createAttributeInternal (final Class<?> attributeClass)
    {
        Attribute attribute = null;

        if (m_constructorsByClass.containsKey (attributeClass))
        {
            try
            {
                final Object object = (m_constructorsByClass.get (attributeClass)).newInstance ();

                if (object instanceof Attribute)
                {
                    attribute = (Attribute) object;
                }
                else
                {
                    WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not create attribute of type : %s.  Resulted in a non Attribute Type.", attributeClass.getName ());
                    WaveAssertUtils.waveAssert ();
                }
            }
            catch (InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not create attribute of type : %s", attributeClass.getName ());
                WaveAssertUtils.waveAssert ();
            }
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "%s is not a supported Attribute Type", attributeClass.getName ());

            WaveAssertUtils.waveAssert ();
        }

        return (attribute);
    }

    public Attribute createAttribute (final Class<?> attributeClass)
    {
        return ((getInstance ()).createAttributeInternal (attributeClass));
    }
}
