/***************************************************************************
 * Copyright (C) 2015-2015 Vhandleyasagara Guntaka * All rights reserved. * Author : Vhandleyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class TimerHandle
{
    private long m_handle;

    public TimerHandle (final long handle)
    {
        m_handle = handle;
    }

    public TimerHandle (final TimerHandle timerHandle)
    {
        m_handle = timerHandle.getHandle ();
    }

    public TimerHandle ()
    {
        m_handle = 0;
    }

    public long getHandle ()
    {
        return (m_handle);
    }

    public void setHandle (final long handle)
    {
        m_handle = handle;
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
}
