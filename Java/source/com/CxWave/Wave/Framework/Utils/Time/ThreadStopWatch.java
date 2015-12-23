/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Time;

import java.lang.management.ManagementFactory;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class ThreadStopWatch
{
    private final Vector<Long> m_lapStarts       = new Vector<Long> ();
    private final Vector<Long> m_lapStops        = new Vector<Long> ();
    private long               m_currentLapStart = 0;

    public ThreadStopWatch ()
    {
    }

    public int getNumberOfLaps ()
    {
        WaveAssertUtils.waveAssert ((m_lapStarts.size ()) == (m_lapStops.size ()));

        return (m_lapStarts.size ());
    }

    public int getNumberOfLapsStarted ()
    {
        return ((m_lapStarts.size ()) + (0 < m_currentLapStart ? 1 : 0));
    }

    public int getNumberOfLapsStoped ()
    {
        return (m_lapStops.size ());
    }

    public long getLapDuration (final int lapIndex)
    {
        if ((lapIndex < (getNumberOfLaps ())) && (0 <= lapIndex))
        {
            return ((m_lapStops.get (lapIndex)) - (m_lapStarts.get (lapIndex)));
        }
        else
        {
            WaveTraceUtils.fatalTracePrintf ("ThreadStopWatch.getLapDuration : LapIndex %d is out of bounds.  Number of Laps : %d", lapIndex, getNumberOfLaps ());
            WaveAssertUtils.waveAssert ();

            return (-1);
        }
    }

    public long getLastLapDuration ()
    {
        final int numberOfLaps = getNumberOfLaps ();

        if (0 < numberOfLaps)
        {
            return (getLapDuration (numberOfLaps - 1));
        }
        else
        {
            return (0);
        }
    }

    public void start ()
    {
        long startThreadCpuTime = 0;

        try
        {
            startThreadCpuTime = (ManagementFactory.getThreadMXBean ()).getCurrentThreadCpuTime ();
        }
        catch (final UnsupportedOperationException e)
        {
            WaveTraceUtils.warnTracePrintf ("ThreadStopWatch.start : Could not collect current thread cpu time.  Details : %s", e.toString ());
        }

        m_currentLapStart = startThreadCpuTime;
    }

    public void stop ()
    {
        // Deliberately using the order below (stop first and then add the start from already recorded variable).

        long stopThreadCpuTime = 0;

        try
        {
            stopThreadCpuTime = (ManagementFactory.getThreadMXBean ()).getCurrentThreadCpuTime ();
        }
        catch (final UnsupportedOperationException e)
        {
            WaveTraceUtils.warnTracePrintf ("ThreadStopWatch.stop : Could not collect current thread cpu time.  Details : %s", e.toString ());
        }

        m_lapStops.add (stopThreadCpuTime);

        WaveAssertUtils.waveAssert (0 != m_currentLapStart);
        m_lapStarts.add (m_currentLapStart);

        m_currentLapStart = 0;
    }
}
