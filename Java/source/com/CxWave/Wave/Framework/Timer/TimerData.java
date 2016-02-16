/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.WaveServiceId;

public class TimerData implements Comparable<TimerData>
{
    private TimeValue                  m_periodicInterval;
    private TimeValue                  m_expirationTime;
    private TimerHandle                m_timerId;
    private WaveTimerExpirationHandler m_waveTimerExpirationCallback;
    private Object                     m_waveTimerExpirationContext;
    private WaveElement                m_waveTimerSender;
    private WaveServiceId              m_serviceId;

    @Override
    public int compareTo (final TimerData rhs)
    {
        return (m_expirationTime.compareTo (rhs.m_expirationTime));
    }

    public TimeValue getPeriodicInterval ()
    {
        return m_periodicInterval;
    }

    public void setPeriodicInterval (final TimeValue periodicInterval)
    {
        m_periodicInterval = periodicInterval;
    }

    public TimeValue getExpirationTime ()
    {
        return m_expirationTime;
    }

    public void setExpirationTime (final TimeValue expirationTime)
    {
        m_expirationTime = expirationTime;
    }

    public TimerHandle getTimerId ()
    {
        return m_timerId;
    }

    public void setTimerId (final TimerHandle timerId)
    {
        m_timerId = timerId;
    }

    public WaveTimerExpirationHandler getWaveTimerExpirationCallback ()
    {
        return m_waveTimerExpirationCallback;
    }

    public void setWaveTimerExpirationCallback (final WaveTimerExpirationHandler waveTimerExpirationCallback)
    {
        m_waveTimerExpirationCallback = waveTimerExpirationCallback;
    }

    public Object getWaveTimerExpirationContext ()
    {
        return m_waveTimerExpirationContext;
    }

    public void setWaveTimerExpirationContext (final Object waveTimerExpirationContext)
    {
        m_waveTimerExpirationContext = waveTimerExpirationContext;
    }

    public WaveElement getWaveTimerSender ()
    {
        return m_waveTimerSender;
    }

    public void setWaveTimerSender (final WaveElement waveTimerSender)
    {
        m_waveTimerSender = waveTimerSender;
    }

    public WaveServiceId getServiceId ()
    {
        return m_serviceId;
    }

    public void setServiceId (final WaveServiceId serviceId)
    {
        m_serviceId = serviceId;
    }
}
