/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.PrePhase;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@PrePhase
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_TIMER)
public class TimerObjectManager extends WaveLocalObjectManager
{
    private static TimerObjectManager s_timerObjectManager = null;

    private TimerObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Timer");
    }

    public static TimerObjectManager getInstance ()
    {
        if (null == s_timerObjectManager)
        {
            s_timerObjectManager = new TimerObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_timerObjectManager);

        return (s_timerObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
