/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer.Test;

import com.CxWave.Wave.Framework.Type.TimeValue;

public class TimerTestData
{
    private FrameworkTimerTestContext m_frameworkTimerTestContext = null;
    private TimeValue                 m_startInterval;
    private TimeValue                 m_periodicInterval;
    private TimeValue                 m_startTime;
    private TimeValue                 m_endTime;
    private TimeValue                 m_expirationTime;
    private int                       m_timerId                   = 0;
    private int                       m_nTimes                    = 0;

    public TimerTestData ()
    {
    }

    public FrameworkTimerTestContext getFrameworkTimerTestContext ()
    {
        return m_frameworkTimerTestContext;
    }

    public void setFrameworkTimerTestContext (final FrameworkTimerTestContext frameworkTimerTestContext)
    {
        m_frameworkTimerTestContext = frameworkTimerTestContext;
    }

    public TimeValue getStartInterval ()
    {
        return m_startInterval;
    }

    public void setStartInterval (final TimeValue startInterval)
    {
        m_startInterval = startInterval;
    }

    public TimeValue getPeriodicInterval ()
    {
        return m_periodicInterval;
    }

    public void setPeriodicInterval (final TimeValue periodicInterval)
    {
        m_periodicInterval = periodicInterval;
    }

    public TimeValue getStartTime ()
    {
        return m_startTime;
    }

    public void setStartTime (final TimeValue startTime)
    {
        m_startTime = startTime;
    }

    public TimeValue getEndTime ()
    {
        return m_endTime;
    }

    public void setEndTime (final TimeValue endTime)
    {
        m_endTime = endTime;
    }

    public TimeValue getExpirationTime ()
    {
        return m_expirationTime;
    }

    public void setExpirationTime (final TimeValue expirationTime)
    {
        m_expirationTime = expirationTime;
    }

    public int getTimerId ()
    {
        return m_timerId;
    }

    public void setTimerId (final int timerId)
    {
        m_timerId = timerId;
    }

    public int getnTimes ()
    {
        return m_nTimes;
    }

    public void setnTimes (final int nTimes)
    {
        m_nTimes = nTimes;
    }
}
