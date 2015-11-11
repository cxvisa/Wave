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
}
