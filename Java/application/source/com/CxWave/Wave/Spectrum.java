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
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.Daemon.DaemonUtils;
import com.CxWave.Wave.Framework.Utils.Debug.DebugUtils;
import com.CxWave.Wave.Framework.Utils.Environment.EnvironmentUtils;
import com.CxWave.Wave.Framework.Utils.LineEditor.WaveLineEditor;
import com.CxWave.Wave.Framework.Utils.Source.SourceUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Framework.Core.Wave;
import com.CxWave.Wave.Framework.Core.WaveBasedApplication;
import com.CxWave.Wave.Framework.Core.Configuration.WaveMainConfiguration;
import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Type.UI32;;

import java.io.Serializable;
import java.util.Vector;

class Spectrum
{
    public static void main (final String[] commandLineArguments)
    {
        WaveMainConfiguration waveMainConfiguration = new WaveMainConfiguration ();

        WaveBasedApplication.waveMain (waveMainConfiguration);

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

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN,       "This is a test. H : " + TimeZoneToolKit.getTimeZoneHours ().getValue () + ", M : " + TimeZoneToolKit.getTimeZoneMinutes ().getValue () + ", DTZ : " + TimeZoneToolKit.getDefaultTimeZone ().toString (), true, false);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "This is a test with tracePrintf : %s, %s", new String ("Successfully traced."), "3016");

        DebugUtils.prettyPrint (WaveJavaSourceRepository.getAllDescendantsForClass (SerializableObject.class.getName ()));

        if (2 <= (commandLineArguments.length))
        {
            XmlFile xmlFile = new XmlFile (commandLineArguments[1]);

            xmlFile.debugPrint ();

            WaveConfigurationFile waveConfigurationFile = new WaveConfigurationFile (commandLineArguments[1]);

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "wave.application.name = %s", waveConfigurationFile.getConfigurationValue ("wave.application.name"));
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "wave.ras.trace.default-level = %s", waveConfigurationFile.getConfigurationValue ("wave.ras.trace.default-level"));

            WaveMainConfiguration waveMainConfiguration1 = new WaveMainConfiguration ();

            waveMainConfiguration1.loadFromWaveConfigurationFile (commandLineArguments[1]);

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Selected Application Name        : %s", (waveMainConfiguration1.getApplication ()).getApplicationName ());
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Selected Application CompactName : %s", waveMainConfiguration1.getApplicationCompactName ());
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Selected Ethernet Interface      : %s", (waveMainConfiguration1.getApplication ()).getEthernetInterface ());

            waveMainConfiguration1.debugPrint ();

            StringBuffer stringBuffer = new StringBuffer ();

            waveMainConfiguration1.serializeTo (stringBuffer);

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Serialized Data for WaveMain Configuration 1:\n%s", stringBuffer);

            UI32 v1 = new UI32 (10);
            UI32 v2 = new UI32 (10);
            UI32 v3 = new UI32 (20);

            if (v1.equals (v2))
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 equals V2");
            }
            else
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 not equals V2");
            }

            if (v1.equals (v3))
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 equals V3");
            }
            else
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 not equals V3");
            }

            WaveMainConfiguration waveMainConfiguration2 = null;

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "loadFromSerializableObject Test (1000000 iterations) started.");

            for (int i = 0; i < 1000000; i++)
            {
                waveMainConfiguration2 = new WaveMainConfiguration ();
                waveMainConfiguration2.loadFromSerializableObject (waveMainConfiguration1);
            }

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "loadFromSerializableObject Test (1000000 iterations) End.");


            stringBuffer.delete (0, stringBuffer.length ());

            waveMainConfiguration2.serializeTo (stringBuffer);

            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Serialized Data for WaveMain Configuration 2:\n%s", stringBuffer);

        }

        if (3 <= (commandLineArguments.length))
        {
            Vector<String> tokens = new Vector<String> ();

            WaveStringUtils.tokenize (commandLineArguments[2], tokens, ' ');

            for (String token : tokens)
            {
                System.out.println ("Token : " + token);
            }
        }

        if (3 <= (commandLineArguments.length))
        {
            Vector<String> tokens = new Vector<String> ();

            WaveStringUtils.tokenizeConsideringStringQuotes (commandLineArguments[2], tokens, ' ');

            for (String token : tokens)
            {
                System.out.println ("Token : " + token);
            }
        }

        WaveLineEditor waveLineEditor = new WaveLineEditor ();

        while (true)
        {
            String command = waveLineEditor.getUserInputLine ("Wave");

            if ("Quit".equals (command))
            {
                break;
            }
        }

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
