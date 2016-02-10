/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;

public class TimerObjectManagerAddTimerMessage extends WaveMessage
{

    protected TimerObjectManagerAddTimerMessage ()
    {
        super (TimerObjectManager.getWaveServiceId (), TimerOpCodes.TIMER_ADD_TIMER);
    }

}
