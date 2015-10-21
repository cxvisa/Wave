/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Trace;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Terminal.WaveTerminalUtils;
import com.CxWave.Wave.Framework.Utils.Time.WaveTimeUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class TraceObjectManager extends WaveObjectManager
{
    private static TraceObjectManager s_traceObjectManager = null;

    private static String        s_waveTraceFileName = null;
    private static boolean       s_isFirstTime       = true;
    private static WaveTraceFile s_waveTraceFile     = new WaveTraceFile ();
    private static WaveMutex     s_mutexForTracing   = new WaveMutex ();

    public static String getClassName ()
    {
        return ("Trace");
    }

    private TraceObjectManager ()
    {
        super (getClassName ());
    }

    public static TraceObjectManager getInstance ()
    {
        if (null == s_traceObjectManager)
        {
            s_traceObjectManager = new TraceObjectManager ();
        }

        return (s_traceObjectManager);
    }

    public static String getWaveTraceFileName ()
    {
        return s_waveTraceFileName;
    }

    public static void setWaveTraceFileName (final String waveTraceFileName)
    {
        s_waveTraceFileName = waveTraceFileName;
    }

    private static String getTraceTagForLevel (final TraceLevel traceLevel)
    {
        String traceTag = null;

        switch (traceLevel)
        {
            case TRACE_LEVEL_UNKNOWN:
                traceTag = "UNKNOWN: ";
                break;

            case TRACE_LEVEL_DEVEL:
                traceTag = "DEVEL  : ";
                break;

            case TRACE_LEVEL_DEBUG:
                traceTag = "DEBUG  : ";
                break;

            case TRACE_LEVEL_INFO:
                traceTag = "INFO   : ";
                break;

            case TRACE_LEVEL_PERF_START:
                traceTag = "PERF_S : ";

                break;

            case TRACE_LEVEL_PERF_END:
                traceTag = "PERF_E : ";
                break;

            case TRACE_LEVEL_SUCCESS:
                traceTag = "SUCCESS: ";
                break;

            case TRACE_LEVEL_WARN:
                traceTag = "WARN   : ";
                break;

            case TRACE_LEVEL_ERROR:
                traceTag = "ERROR  : ";
                break;

            case TRACE_LEVEL_FATAL:
                traceTag = "FATAL  : ";
                break;
        }

        return (traceTag);
    }

    public static void traceDirectly (final TraceClientId traceClientId, final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        s_mutexForTracing.lock ();

        if (s_isFirstTime)
        {
            s_waveTraceFile.setNewFilePath (s_waveTraceFileName);

            s_isFirstTime = false;
        }

        final TraceClientMap traceClientMap = TraceClientMap.getInstance ();

        final TraceLevel currentTraceLevel = traceClientMap.getTraceClientLevel (traceClientId);

        if (0 >= (currentTraceLevel.compareTo (requestedTraceLevel)))
        {
            final StringBuilder computedTraceString = new StringBuilder ();

            WaveTerminalUtils.waveSetConsoleTextColor (requestedTraceLevel);

            if (!suppressPrefix)
            {
                computedTraceString.append (getTraceTagForLevel (requestedTraceLevel));

                computedTraceString.append (WaveTimeUtils.ctime ());

                computedTraceString.append (" : ");
            }

            String newLineString = "";

            if (addNewLine)
            {
                newLineString = "\n";
            }

            s_waveTraceFile.printf ("%s%s%s", computedTraceString, stringToTrace, newLineString);
            s_waveTraceFile.flush ();

            System.out.printf ("%s%s%s", computedTraceString, stringToTrace, newLineString);

            WaveTerminalUtils.waveResetConsoleTextColor ();
        }

        s_mutexForTracing.unlock ();
    }

    public static TraceClientId addClient (final TraceLevel traceLevel, final String traceClientName)
    {
        final TraceClientMap traceClientMap = TraceClientMap.getInstance ();

        WaveAssertUtils.waveAssert (null != traceClientMap);

        final TraceClientId traceClientId = traceClientMap.addClient (traceLevel, traceClientName);

        return (traceClientId);
    }
}
