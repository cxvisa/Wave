/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Type.TimerHandle;

public class TimerObjectManagerDeleteTimerMessage extends WaveMessage
{
    private TimerHandle m_timerId;

    protected TimerObjectManagerDeleteTimerMessage ()
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_DELETE_TIMER);
    }

    protected TimerObjectManagerDeleteTimerMessage (final TimerHandle timerId)
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_DELETE_TIMER);

        m_timerId = timerId;
    }
}
