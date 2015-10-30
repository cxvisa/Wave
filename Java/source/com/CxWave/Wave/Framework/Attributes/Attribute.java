/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.lang.reflect.Field;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public abstract class Attribute
{
    private Object              m_lastValue;
    private ReflectionAttribute m_reflectionAttribute;

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
}
