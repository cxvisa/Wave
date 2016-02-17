/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class TimerHandle implements Comparable<TimerHandle>
{
    public static final TimerHandle NullTimerHandle = new TimerHandle (0);

    private long                    m_handle;

    public TimerHandle (final long handle)
    {
        setValue (handle);
    }

    public TimerHandle (final TimerHandle timerHandle)
    {
        setValue (timerHandle.getHandle ());
    }

    public TimerHandle (final String timerHandle)
    {
        setValue (timerHandle);
    }

    public TimerHandle ()
    {
        m_handle = 0;
    }

    public long getHandle ()
    {
        return (m_handle);
    }

    public void setValue (final long value)
    {
        m_handle = new Long (value);
    }

    public void setValue (final Long value)
    {
        m_handle = new Long (value);
    }

    public void setValue (final String timerHandle)
    {
        try
        {
            setValue (Long.valueOf (timerHandle));
        }
        catch (final NumberFormatException e)
        {
            setValue (0);
        }
    }

    public long increment ()
    {
        m_handle++;

        return (m_handle);
    }

    @Override
    public String toString ()
    {
        return ((new Long (m_handle)).toString ());
    }

    @Override
    public int hashCode ()
    {
        return ((Long.valueOf (m_handle)).hashCode ());
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof TimerHandle))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final TimerHandle rhs = (TimerHandle) object;

        return (m_handle == rhs.m_handle);
    }

    @Override
    public int compareTo (final TimerHandle rhs)
    {
        return ((new Long (m_handle)).compareTo (rhs.m_handle));
    }

    public void setHandle (final TimerHandle timerId)
    {
        setValue (timerId.getHandle ());
    }

    public void setHandle (final long value)
    {
        setValue (value);
    }
}
