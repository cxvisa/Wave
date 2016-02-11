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
    private TimerHandle                m_timeHandle;
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

    public TimeValue getM_startInterval ()
    {
        return m_startInterval;
    }

    public void setM_startInterval (final TimeValue m_startInterval)
    {
        this.m_startInterval = m_startInterval;
    }

    public TimeValue getM_periodicInterval ()
    {
        return m_periodicInterval;
    }

    public void setM_periodicInterval (final TimeValue m_periodicInterval)
    {
        this.m_periodicInterval = m_periodicInterval;
    }

    public TimeValue getM_startTime ()
    {
        return m_startTime;
    }

    public void setM_startTime (final TimeValue m_startTime)
    {
        this.m_startTime = m_startTime;
    }

    public TimerHandle getM_timeHandle ()
    {
        return m_timeHandle;
    }

    public void setM_timeHandle (final TimerHandle m_timeHandle)
    {
        this.m_timeHandle = m_timeHandle;
    }

    public WaveTimerExpirationHandler getM_waveTimerExpirationCallback ()
    {
        return m_waveTimerExpirationCallback;
    }

    public void setM_waveTimerExpirationCallback (final WaveTimerExpirationHandler m_waveTimerExpirationCallback)
    {
        this.m_waveTimerExpirationCallback = m_waveTimerExpirationCallback;
    }

    public Object getM_waveTimerExpirationContext ()
    {
        return m_waveTimerExpirationContext;
    }

    public void setM_waveTimerExpirationContext (final Object m_waveTimerExpirationContext)
    {
        this.m_waveTimerExpirationContext = m_waveTimerExpirationContext;
    }

    public WaveElement getM_waveTimerSender ()
    {
        return m_waveTimerSender;
    }

    public void setM_waveTimerSender (final WaveElement m_waveTimerSender)
    {
        this.m_waveTimerSender = m_waveTimerSender;
    }
}
