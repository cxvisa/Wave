/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Synchronization;

import java.util.concurrent.locks.Condition;

import com.CxWave.Wave.Framework.Utils.Stack.WaveStackUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveCondition
{
    private final WaveMutex m_waveMutex;
    private Condition       m_condition;

    public WaveCondition (final WaveMutex waveMutex)
    {
        m_waveMutex = waveMutex;

        if (null != m_waveMutex)
        {
            m_condition = m_waveMutex.newCondition ();
        }
        else
        {
            throw (new NullPointerException ());
        }
    }

    public WaveConditionStatus awaitUninterruptibly ()
    {
        try
        {
            m_condition.awaitUninterruptibly ();
        }
        catch (final IllegalMonitorStateException illegalMonitorStateException)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveCondition.awaitUninterruptibly : When awaitUninterruptibly was called, corresponding mutex was not locked.");

            return (WaveConditionStatus.WAVE_CONDITION_ILLEGAL_STATE);
        }

        return (WaveConditionStatus.WAVE_CONDITION_SUCCESS);
    }

    public WaveConditionStatus awaitNanos (final long nanos)
    {
        try
        {
            m_condition.awaitNanos (nanos);
        }
        catch (final InterruptedException e)
        {
            WaveTraceUtils.warnTracePrintf ("WaveCondition.awaitNanos : %s", WaveStackUtils.getStackString (e));

            return (WaveConditionStatus.WAVE_CONDITION_INTERRUPTED);
        }
        catch (final IllegalMonitorStateException illegalMonitorStateException)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveCondition.awaitNanos : When awaitNanos was called, corresponding mutex was not locked.");

            return (WaveConditionStatus.WAVE_CONDITION_ILLEGAL_STATE);
        }

        return (WaveConditionStatus.WAVE_CONDITION_SUCCESS);
    }

    public WaveConditionStatus signal ()
    {
        try
        {
            m_condition.signal ();
        }
        catch (final IllegalMonitorStateException illegalMonitorStateException)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveCondition.signal : When signal was called, corresponding mutex was not locked.");

            return (WaveConditionStatus.WAVE_CONDITION_ILLEGAL_STATE);
        }

        return (WaveConditionStatus.WAVE_CONDITION_SUCCESS);
    }

    public WaveConditionStatus signalAll ()
    {
        try
        {
            m_condition.signalAll ();
        }
        catch (final IllegalMonitorStateException illegalMonitorStateException)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveCondition.signalAll : When signaAlll was called, corresponding mutex was not locked.");

            return (WaveConditionStatus.WAVE_CONDITION_ILLEGAL_STATE);
        }

        return (WaveConditionStatus.WAVE_CONDITION_SUCCESS);
    }
}
