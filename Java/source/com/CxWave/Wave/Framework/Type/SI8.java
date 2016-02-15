/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class SI8 implements Comparable<SI8>
{
    private Byte m_value;

    public SI8 (final byte value)
    {
        setValue (value);
    }

    public SI8 (final long value)
    {
        setValue (value);
    }

    public SI8 (final SI8 rhs)
    {
        setValue (rhs);
    }

    public SI8 (final String value)
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

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof SI8))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final SI8 rhs = (SI8) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public byte getValue ()
    {
        return (m_value);
    }

    public void setValue (final byte value)
    {
        m_value = new Byte (value);
    }

    public void setValue (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = (byte) value;
    }

    public void setValue (final SI8 rhs)
    {
        m_value = new Byte (rhs.getValue ());
    }

    public boolean isValid (final long value)
    {
        if ((128 > value) && (-128 <= value))
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

    public boolean equals (final SI8 rhs)
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

    @Override
    public int compareTo (final SI8 rhs)
    {
        return (m_value.compareTo (rhs.m_value));
    }
}
