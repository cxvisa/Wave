/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class UI32 implements Comparable<UI32>
{
    private Long       m_value;

    public static UI32 MAXIMUM = new UI32 ((0x1L << 32) - 1L);
    public static UI32 MINIMUM = new UI32 (0);

    public UI32 (final Integer value)
    {
        setValue (value);
    }

    public UI32 (final String value)
    {
        try
        {
            setValue (Long.valueOf (value));
        }
        catch (final NumberFormatException e)
        {
            setValue (0);
        }
    }

    public UI32 (final long value)
    {
        setValue (value);
    }

    public UI32 (final UI32 rhs)
    {
        setValue (rhs);
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof UI32))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final UI32 rhs = (UI32) object;

        if (m_value.equals ((rhs.getValue ())))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public Long getValue ()
    {
        return (m_value.longValue ());
    }

    public void setValue (final int value)
    {
        if (!(isValid (value)))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "Invalid Value : " + value, true, false);

            WaveAssertUtils.waveAssert ();
        }

        m_value = new Long (value);
    }

    public void setValue (final Integer value)
    {
        if (!(isValid (value)))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "Invalid Value : " + value, true, false);

            WaveAssertUtils.waveAssert ();
        }

        m_value = value.longValue ();
    }

    public void setValue (final UI32 rhs)
    {
        m_value = new Long (rhs.getValue ());
    }

    public void setValue (final long value)
    {
        if (!(isValid (value)))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "Invalid Value : " + value, true, false);

            WaveAssertUtils.waveAssert ();
        }

        m_value = new Long (value);
    }

    public boolean isValid (final long value)
    {
        if ((0 <= value) && ((1L << 32) > value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public void increment ()
    {
        m_value++;
    }

    public void increment (final int value)
    {
        m_value = m_value + value;
    }

    public void increment (final UI32 value)
    {
        m_value = m_value.longValue () + (value.getValue ());
    }

    public void decrement ()
    {
        m_value--;
    }

    public void decrement (final int value)
    {
        m_value = m_value - value;
    }

    public boolean equals (final UI32 rhs)
    {
        return (m_value.equals (rhs.m_value));
    }

    @Override
    public String toString ()
    {
        return (m_value.toString ());
    }

    @Override
    public int hashCode ()
    {
        return (m_value.hashCode ());
    }

    public int intValue ()
    {
        return (m_value.intValue ());
    }

    @Override
    public int compareTo (final UI32 rhs)
    {
        return (m_value.compareTo (rhs.m_value));
    }
}
