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

    private Field getReflectionField ()
    {
        return (m_reflectionAttribute.getField ());
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
                // TODO Auto-generated catch block
                e.printStackTrace ();

                WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "Could not get current Value via field.", true, false);
                WaveAssertUtils.waveAssert ();
            }
        }

        return (currentValue);
    }
}
