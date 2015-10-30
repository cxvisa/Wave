/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class SI32
{
    private Integer m_value;

    public SI32 (final Integer value)
    {
        setValue (value);
    }

    public SI32 (final long value)
    {
        setValue (value);
    }

    public SI32 (final SI32 rhs)
    {
        setValue (rhs);
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof SI32))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final SI32 rhs = (SI32) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public Integer getValue ()
    {
        return (m_value);
    }

    public void seValue (final int value)
    {
        m_value = new Integer (value);
    }

    public void setValue (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = new Integer ((int) value);
    }

    public void setValue (final SI32 rhs)
    {
        m_value = new Integer (rhs.getValue ());
    }

    public boolean isValid (final long value)
    {
        if (((1 << 31) > value) && ((-(1 << 31)) <= value))
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

    public void decrement ()
    {
        m_value--;
    }

    public boolean equals (final SI32 rhs)
    {
        return (m_value.equals (rhs.m_value));
    }
}
