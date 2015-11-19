/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.MultiThreading;

import com.CxWave.Wave.Framework.Type.UI32;

public class WaveThreadId
{
    private long m_threadId;

    public WaveThreadId ()
    {
        m_threadId = 0;
    }

    public WaveThreadId (final long threadId)
    {
        m_threadId = threadId;
    }

    public WaveThreadId (final UI32 threadId)
    {
        m_threadId = threadId.getValue ();
    }

    public long getThreadId ()
    {
        return (m_threadId);
    }

    public void setThreadId (final long threadId)
    {
        m_threadId = threadId;
    }

    public boolean isValid ()
    {
        if (0 != m_threadId)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    @Override
    public String toString ()
    {
        String stringRepresentation = null;

        stringRepresentation = "" + m_threadId;

        return (stringRepresentation);
    }

    @Override
    public int hashCode ()
    {
        // Based on Effective Java code.

        int result = 0x9101;

        final int hash = (int) (m_threadId ^ (m_threadId >>> 32));

        result = (37 * result) + hash;

        return (result);
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof WaveThreadId))
        {
            return (false);
        }

        final WaveThreadId waveThreadId = (WaveThreadId) object;

        return (m_threadId == waveThreadId.m_threadId);
    }
}
