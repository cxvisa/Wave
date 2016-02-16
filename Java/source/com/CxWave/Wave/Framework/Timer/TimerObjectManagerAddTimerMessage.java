/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;

public class TimerObjectManagerAddTimerMessage extends WaveMessage
{
    private TimeValue                  m_startInterval;
    private TimeValue                  m_periodicInterval;
    private TimeValue                  m_startTime;
    private TimerHandle                m_timerId;
    private WaveTimerExpirationHandler m_waveTimerExpirationCallback;
    private Object                     m_waveTimerExpirationContext;
    private WaveElement                m_waveTimerSender;

    public TimerObjectManagerAddTimerMessage ()
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_ADD_TIMER);
    }

    public TimerObjectManagerAddTimerMessage (final TimeValue startInterval, final TimeValue periodicInterval, final TimeValue startTime, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_ADD_TIMER);

        m_startInterval = startInterval;
        m_periodicInterval = periodicInterval;
        m_startTime = startTime;
        m_waveTimerExpirationCallback = waveTimerExpirationCallback;
        m_waveTimerExpirationContext = waveTimerExpirationContext;
        m_waveTimerSender = waveTimerSender;
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

}
