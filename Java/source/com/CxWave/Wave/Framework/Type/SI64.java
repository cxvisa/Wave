/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class SI64
{
    private Long m_value;

    public SI64 (final Long value)
    {
        setValue (value);
    }

    public SI64 (final long value)
    {
        setValue (value);
    }

    public SI64 (final int value)
    {
        setValue (value);
    }

    public SI64 (final SI64 rhs)
    {
        setValue (rhs);
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof SI64))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final SI64 rhs = (SI64) object;

        if (m_value == (rhs.getValue ()))
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
        return (m_value);
    }

    public void setValue (final long value)
    {
        m_value = new Long (value);
    }

    public void setValue (final Long value)
    {
        m_value = new Long (value);
    }

    public void setValue (final SI64 rhs)
    {
        m_value = new Long (rhs.getValue ());
    }

    public void increment ()
    {
        m_value++;
    }

    public void decrement ()
    {
        m_value--;
    }

    public boolean equals (final SI64 rhs)
    {
        return (m_value.equals (rhs.m_value));
    }

    @Override
    public String toString ()
    {
        return (m_value.toString ());
    }
}
