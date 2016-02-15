/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class SI16 implements Comparable<SI16>
{
    private Short m_value;

    public SI16 (final short value)
    {
        setValue (value);
    }

    public SI16 (final long value)
    {
        setValue (value);
    }

    public SI16 (final SI16 rhs)
    {
        setValue (rhs);
    }

    public SI16 (final String value)
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

        if (!(object instanceof SI16))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final SI16 rhs = (SI16) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public Short getValue ()
    {
        return (m_value);
    }

    public void setValue (final short value)
    {
        m_value = new Short (value);
    }

    public void setValue (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = (short) value;
    }

    public void setValue (final SI16 rhs)
    {
        m_value = new Short (rhs.getValue ());
    }

    public boolean isValid (final long value)
    {
        if (((1 << 15) > value) && ((-(1 << 15)) <= value))
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

    public boolean equals (final SI16 rhs)
    {
        return (m_value.equals (rhs.m_value));
    }

    @Override
    public String toString ()
    {
        return (m_value.toString ());
    }

    @Override
    public int compareTo (final SI16 rhs)
    {
        return (m_value.compareTo (rhs.m_value));
    }
}
