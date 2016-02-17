/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Type.TimerHandle;

public class TimerObjectManagerDeleteTimerMessage extends WaveMessage
{
    private TimerHandle m_timerId;

    public TimerObjectManagerDeleteTimerMessage ()
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_DELETE_TIMER);
    }

    public TimerObjectManagerDeleteTimerMessage (final TimerHandle timerId)
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_DELETE_TIMER);

        m_timerId = timerId;
    }

    public TimerHandle getTimerId ()
    {
        return m_timerId;
    }

    public void setTimerId (final TimerHandle timerId)
    {
        m_timerId = timerId;
    }
}
