/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class TimeValue implements Comparable<TimeValue>
{
    private long            m_milliSeconds = 0;
    private int             m_nanoSeconds  = 0;

    public static final int MAX_NANOS      = 999999;

    public TimeValue ()
    {
    }

    public TimeValue (final long milliSeconds)
    {
        m_milliSeconds = milliSeconds;
        m_nanoSeconds = 0;
    }

    public TimeValue (final long milliSeconds, final int nanoSeconds)
    {
        m_milliSeconds = milliSeconds;
        m_nanoSeconds = nanoSeconds;

        normalize ();
    }

    public void normalize ()
    {
        if (MAX_NANOS < m_nanoSeconds)
        {
            m_milliSeconds += m_nanoSeconds / 1000000;
            m_nanoSeconds %= 1000000;
        }
    }

    @Override
    public int compareTo (final TimeValue rhs)
    {
        if (m_milliSeconds < rhs.m_milliSeconds)
        {
            return (-1);
        }
        else if (m_milliSeconds > rhs.m_milliSeconds)
        {
            return (1);
        }
        else
        {
            if (m_nanoSeconds < rhs.m_nanoSeconds)
            {
                return (-1);
            }
            else if (m_nanoSeconds > rhs.m_nanoSeconds)
            {
                return (1);
            }
            else
            {
                return (0);
            }
        }
    }
}
