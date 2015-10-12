/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Terminal;

import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveTerminalUtils
{
    private WaveTerminalUtils ()
    {
    }

    public static void waveSetConsoleTextColor (TraceLevel requestedTraceLevel)
    {
        switch (requestedTraceLevel)
        {
            case TRACE_LEVEL_UNKNOWN:
                System.out.print ("\033[34m");
                break;

            case TRACE_LEVEL_DEVEL:
                System.out.print ("\033[36m");
                break;

            case TRACE_LEVEL_DEBUG:
                System.out.print ("\033[35m");
                break;

            case TRACE_LEVEL_INFO:
                break;

            case TRACE_LEVEL_PERF_START:
                break;

            case TRACE_LEVEL_PERF_END:
                break;

            case TRACE_LEVEL_SUCCESS:
                System.out.print ("\033[32m");
                break;

            case TRACE_LEVEL_WARN:
                System.out.print ("\033[33m");
                break;

            case TRACE_LEVEL_ERROR:
                System.out.print ("\033[31m");
                break;

            case TRACE_LEVEL_FATAL:
                System.out.print ("\033[37;41;1m");
                break;
        }
    }

    public static void waveResetConsoleTextColor ()
    {
        System.out.print ("\033[0m");
    }
}
