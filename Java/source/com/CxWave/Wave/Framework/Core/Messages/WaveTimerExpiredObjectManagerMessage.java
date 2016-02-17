/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Messages;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.FrameworkOpCodes;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.WaveServiceId;

public class WaveTimerExpiredObjectManagerMessage extends WaveMessage
{
    private TimerHandle                m_timerId;
    @NonSerializable
    private WaveTimerExpirationHandler m_waveTimerExpirationCallback;
    @NonSerializable
    private Object                     m_waveTimerExpirationContext;
    @NonSerializable
    private WaveElement                m_waveTimerSender;

    public WaveTimerExpiredObjectManagerMessage ()
    {
        super (WaveServiceId.NullServiceId, FrameworkOpCodes.WAVE_OBJECT_MANAGER_TIMER_EXPIRED);
    }

    public WaveTimerExpiredObjectManagerMessage (final WaveServiceId serviceCode, final TimerHandle timerId, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender)
    {
        super (serviceCode, FrameworkOpCodes.WAVE_OBJECT_MANAGER_TIMER_EXPIRED);

        m_timerId = timerId;
        m_waveTimerExpirationCallback = waveTimerExpirationCallback;
        m_waveTimerExpirationContext = waveTimerExpirationContext;
        m_waveTimerSender = waveTimerSender;
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
