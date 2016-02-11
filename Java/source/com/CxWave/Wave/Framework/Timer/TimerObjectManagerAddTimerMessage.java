/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;

public class TimerObjectManagerAddTimerMessage extends WaveMessage
{
    private TimeValue   m_startInterval;
    private TimeValue   m_periodicInterval;
    private TimeValue   m_startTime;
    private TimerHandle m_timeHandle;

    protected TimerObjectManagerAddTimerMessage ()
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_ADD_TIMER);
    }

}
