/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.WaveServiceId;

public class TimerData implements Comparable<TimerData>
{
    private TimeValue                  m_periodicInterval;
    private TimeValue                  m_expirationTime;
    private TimerHandle                m_timerId;
    private WaveTimerExpirationHandler m_waveTimerExpirationCallback;
    private Object                     m_waveTimerExpirationContext;
    private WaveElement                m_waveTimerSender;
    private WaveServiceId              m_serviceId;

    @Override
    public int compareTo (final TimerData rhs)
    {
        return (m_expirationTime.compareTo (rhs.m_expirationTime));
    }

}
