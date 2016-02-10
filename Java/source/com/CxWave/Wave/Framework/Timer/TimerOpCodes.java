/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;

public enum TimerOpCodes implements WaveOperationCodeInterface
{
    TIMER_ADD_TIMER,
    TIMER_DELETE_TIMER,
    TIMER_DELETE_ALL_TIMERS_FOR_SERVICE;

    @Override
    public UI32 getOperationCode ()
    {
        return (new UI32 (ordinal ()));
    }

    @Override
    public int getOperationCodeIntValue ()
    {
        return (ordinal ());
    }
}
