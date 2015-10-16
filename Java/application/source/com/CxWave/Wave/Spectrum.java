/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave;

import com.CxWave.Wave.Framework.ToolKits.TimeZone.TimeZoneToolKit;
import com.CxWave.Wave.Framework.ToolKits.Xml.XmlFile;
import com.CxWave.Wave.Framework.Trace.TraceClientMap;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Trace.WaveTraceFile;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Daemon.DaemonUtils;
import com.CxWave.Wave.Framework.Utils.Debug.DebugUtils;
import com.CxWave.Wave.Framework.Utils.Environment.EnvironmentUtils;
import com.CxWave.Wave.Framework.Utils.Source.SourceUtils;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Framework.Core.Wave;

class Spectrum
{
    public static void main (final String[] commandLineArguments)
    {
        EnvironmentUtils.recordAllCommandLineArguments ();

        System.out.println ("Print JVM Command Line Arguments : " + (EnvironmentUtils.getVirtualMachineCommandLineArguments ()).toString ());

        System.out.println ("Print CLASSPATH Command Line Arguments : " + (EnvironmentUtils.getClassPathCommandLineArguments ()).toString ());

        System.out.println ("List of all files in the dir : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllFilesInTheDirectory (commandLineArguments[0]));

        System.out.println ("List of all dirs in the dir : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllDirectoriesInTheDirectory (commandLineArguments[0]));

        System.out.println ("List of all files only in the dir : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllFilesOnlyInTheDirectory (commandLineArguments[0]));

        System.out.println ("List of all Available JAR Files : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllAvailableJarFiles ());

        System.out.println ("List of all Available Class Files From All Available Jar Files : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllAvailableClassFilesFromAllAvailableJarFiles ());

        System.out.println ("List of all Available Class Path Directories : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllAvailableClassPathDirectories ());

        System.out.println ("List of all Available Class Files From All Available Class Path Directories : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllAvailableClassFilesFromAllAvailableClassPathDirectories ());

        System.out.println ("List of all Available Class Files Relative to  All Available Class Path Directories : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories ());

        System.out.println ("List of all Available Classes : ");

        DebugUtils.prettyPrint (SourceUtils.getListOfAllAvailableClasses ());

        System.out.println ("Just before Daemonize ...");

        TraceObjectManager tom = TraceObjectManager.getInstance ();

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_UNKNOWN, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_UNKNOWN, "This is a test\n", false, true);

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_UNKNOWN,    "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEVEL,      "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEBUG,      "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO,       "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_PERF_START, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_PERF_END  , "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_SUCCESS,    "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN,       "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_ERROR,      "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL,      "This is a test", true, false);

        Wave.initialize (null);

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN,       "This is a test. H : " + TimeZoneToolKit.getTimeZoneHours ().getValue () + ", M : " + TimeZoneToolKit.getTimeZoneMinutes ().getValue () + ", DTZ : " + TimeZoneToolKit.getDefaultTimeZone ().toString (), true, false);

        XmlFile xmlFile = new XmlFile (commandLineArguments[1]);

        xmlFile.debugPrint ();

        DaemonUtils.daemonize ();

        while (true)
        {
            try
            {
                System.out.println ("After Daemonize ...");
                Thread.sleep (1000);
            }
            catch (Exception exception)
            {
                System.out.println ("Failed to sleep.");
                break;
            }
        }

        WaveAssertUtils.waveAssert (false);
    }
}
