/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;

public class TimerObjectManagerDeleteAllTimersForServiceMessage extends WaveMessage
{

    protected TimerObjectManagerDeleteAllTimersForServiceMessage ()
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_DELETE_ALL_TIMERS_FOR_SERVICE);
    }
}
