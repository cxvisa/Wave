/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class TimeValue implements Comparable<TimeValue>
{
    private long                  m_milliSeconds = 0;
    private int                   m_nanoSeconds  = 0;

    public static final int       NANOS_IN_MILLI = 1000000;
    public static final int       MAX_NANOS      = NANOS_IN_MILLI - 1;

    public static final TimeValue IMMEDIATE      = new TimeValue (0, 0);

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

    public TimeValue (final TimeValue timeValue)
    {
        m_milliSeconds = timeValue.m_milliSeconds;
        m_nanoSeconds = timeValue.m_nanoSeconds;

        normalize ();
    }

    public void normalize ()
    {
        if (MAX_NANOS < m_nanoSeconds)
        {
            m_milliSeconds += m_nanoSeconds / NANOS_IN_MILLI;
            m_nanoSeconds %= NANOS_IN_MILLI;
        }
    }

    public long getMilliSeconds ()
    {
        return (m_milliSeconds);
    }

    public long getNanoSeconds ()
    {
        return (m_nanoSeconds);
    }

    public void add (final TimeValue timeValue)
    {
        m_milliSeconds += timeValue.m_milliSeconds;
        m_nanoSeconds += timeValue.m_nanoSeconds;

        normalize ();
    }

    public void resetToDiff (final TimeValue timeValue)
    {
        m_milliSeconds -= timeValue.m_milliSeconds;
        m_nanoSeconds -= timeValue.m_nanoSeconds;

        if ((m_milliSeconds > 0) && (m_nanoSeconds < 0))
        {
            m_milliSeconds -= 1;
            m_nanoSeconds += NANOS_IN_MILLI;
        }
        else if ((m_milliSeconds < 0) && (m_nanoSeconds < 0))
        {
            m_milliSeconds *= -1;
            m_nanoSeconds *= -1;
        }
        else if ((m_milliSeconds == 0) && (m_nanoSeconds < 0))
        {
            m_nanoSeconds *= -1;
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

    public void resetToCurrent ()
    {
        final long nanos = System.nanoTime ();

        m_milliSeconds = nanos / NANOS_IN_MILLI;
        m_nanoSeconds = (int) (nanos % NANOS_IN_MILLI);
    }

    public long getValueInNanos ()
    {
        return ((m_milliSeconds * NANOS_IN_MILLI) + m_nanoSeconds);
    }

    public boolean isValid ()
    {
        normalize ();

        if ((0 <= m_milliSeconds) && (0 <= m_nanoSeconds) && (NANOS_IN_MILLI > m_nanoSeconds))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public boolean isNonImmediate ()
    {
        if (!(isValid ()))
        {
            return (false);
        }
        else
        {
            if ((0 != m_milliSeconds) || (0 != m_nanoSeconds))
            {
                return (true);
            }
            else
            {
                return (false);
            }
        }
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof TimeValue))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final TimeValue rhs = (TimeValue) object;

        return ((m_milliSeconds == rhs.m_milliSeconds) && (m_nanoSeconds == rhs.m_nanoSeconds));
    }

    @Override
    public String toString ()
    {
        return (String.format ("%d:%06d", m_milliSeconds, m_nanoSeconds));
    }
}
