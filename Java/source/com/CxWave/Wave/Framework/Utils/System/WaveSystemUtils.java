/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.System;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveSystemUtils
{
    private WaveSystemUtils ()
    {
    }

    public static Vector<String> runSystemCommand (final String[] systemCommandLines)
    {
        final Runtime runtime = Runtime.getRuntime ();

        final Vector<String> outputLines = new Vector<String> ();

        Process process = null;

        try
        {
            process = runtime.exec (systemCommandLines);
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to execute the command : %s, status : %s", systemCommandLines[0], e.toString ());
        }

        if (null != process)
        {
            try
            {
                process.waitFor ();
            }
            catch (final InterruptedException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to wait for the executed command : %s, status : %s", systemCommandLines[0], e.toString ());
            }
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to execute the command : %s.  Got a null process.", systemCommandLines[0]);

            return (outputLines);
        }

        final BufferedReader bufferedReader = new BufferedReader (new InputStreamReader (process.getInputStream ()));

        String outputLine = null;

        try
        {
            while (null != (outputLine = (bufferedReader.readLine ())))
            {
                outputLines.add (outputLine);
            }
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to read output for the executed command : %s, status : %s", systemCommandLines[0], e.toString ());
        }

        return (outputLines);
    }
}
