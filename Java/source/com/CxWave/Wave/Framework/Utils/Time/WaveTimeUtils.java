/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Time;

import java.lang.management.ManagementFactory;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class WaveTimeUtils
{
    private WaveTimeUtils ()
    {
    }

    public void initialize ()
    {
    }

    public boolean enableThreadCpuTime ()
    {
        boolean isSuccessful = true;

        try
        {
            (ManagementFactory.getThreadMXBean ()).setThreadCpuTimeEnabled (true);

            isSuccessful = true;
        }
        catch (UnsupportedOperationException | SecurityException e)
        {
            isSuccessful = false;
        }

        return (isSuccessful);
    }

    public boolean disableThreadCpuTime ()
    {
        boolean isSuccessful = true;

        try
        {
            (ManagementFactory.getThreadMXBean ()).setThreadCpuTimeEnabled (false);

            isSuccessful = true;
        }
        catch (UnsupportedOperationException | SecurityException e)
        {
            isSuccessful = false;
        }

        return (isSuccessful);
    }

    public long getCurrentThreadCpuTime ()
    {
        return ((ManagementFactory.getThreadMXBean ()).getCurrentThreadCpuTime ());
    }

    public long getCurrentThreadUserTime ()
    {
        return ((ManagementFactory.getThreadMXBean ()).getCurrentThreadUserTime ());
    }

    public static String ctime ()
    {
        final LocalDateTime localDateTime = LocalDateTime.now ();
        final DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern ("EEE MMM dd HH:mm:ss yyyy");
        final String formattedDateTime = localDateTime.format (dateTimeFormatter);

        return (formattedDateTime);
    }
}
