/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave;

import java.lang.management.ManagementFactory;
import java.util.Vector;

import com.CxWave.Wave.Framework.Core.WaveBasedApplication;
import com.CxWave.Wave.Framework.Core.Configuration.WaveMainConfiguration;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ToolKits.TimeZone.TimeZoneToolKit;
import com.CxWave.Wave.Framework.ToolKits.Xml.XmlFile;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.Debug.DebugUtils;
import com.CxWave.Wave.Framework.Utils.Environment.EnvironmentUtils;
import com.CxWave.Wave.Framework.Utils.Network.WaveNetworkUtils;
import com.CxWave.Wave.Framework.Utils.Source.SourceUtils;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

class Spectrum
{
    public static void main (final String[] commandLineArguments)
    {
        final boolean threadCpuTimeSupport = ManagementFactory.getThreadMXBean ().isThreadCpuTimeSupported ();

        if (threadCpuTimeSupport)
        {
            System.out.println ("Thread CPU Time Support is supported.");
        }
        else
        {
            System.out.println ("Thread CPU Time Support is NOT supported.");
        }

        final boolean threadCpuTimeEnabled = ManagementFactory.getThreadMXBean ().isThreadCpuTimeEnabled ();

        if (threadCpuTimeEnabled)
        {
            System.out.println ("Thread CPU Time Support is enabled.");
        }
        else
        {
            System.out.println ("Thread CPU Time Support is NOT enabled.");
        }

        String configurationFile = null;

        if (2 <= (commandLineArguments.length))
        {
            configurationFile = commandLineArguments[1];
        }

        WaveBasedApplication.waveMain (configurationFile);

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

        final TraceObjectManager tom = TraceObjectManager.getInstance ();

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_UNKNOWN, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_UNKNOWN, "This is a test\n", false, true);

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_UNKNOWN, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEVEL, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEBUG, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_INFO, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_PERF_START, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_PERF_END, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_SUCCESS, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_ERROR, "This is a test", true, false);
        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "This is a test", true, false);

        WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN, "This is a test. H : " + TimeZoneToolKit.getTimeZoneHours ().getValue () + ", M : " + TimeZoneToolKit.getTimeZoneMinutes ().getValue () + ", DTZ : " + TimeZoneToolKit.getDefaultTimeZone ().toString (), true, false);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "This is a test with tracePrintf : %s, %s", new String ("Successfully traced."), "3016");

        DebugUtils.prettyPrint (WaveJavaSourceRepository.getAllDescendantsForClass (SerializableObject.class.getName ()));

        if (3 <= (commandLineArguments.length))
        {
            final Vector<String> tokens = new Vector<String> ();

            WaveStringUtils.tokenize (commandLineArguments[2], tokens, ' ');

            for (final String token : tokens)
            {
                System.out.println ("Token : " + token);
            }
        }

        if (3 <= (commandLineArguments.length))
        {
            final Vector<String> tokens = new Vector<String> ();

            WaveStringUtils.tokenizeConsideringStringQuotes (commandLineArguments[2], tokens, ' ');

            for (final String token : tokens)
            {
                System.out.println ("Token : " + token);
            }
        }

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "All Ip Addresses for this machine : ");

        final Vector<String> allIpAddresses = WaveNetworkUtils.getAllIpAddressesForThisMachine ();

        DebugUtils.prettyPrint (allIpAddresses);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "All Ip Addresses That are up for this machine : ");

        final Vector<String> allIpAddressesThatAreUp = WaveNetworkUtils.getAllIpAddressesThatAreUpForThisMachine ();

        DebugUtils.prettyPrint (allIpAddressesThatAreUp);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "All IpV4 Addresses That are up for this machine : ");

        final Vector<String> allIpV4AddressesThatAreUp = WaveNetworkUtils.getAllIpV4AddressesThatAreUpForThisMachine ();

        DebugUtils.prettyPrint (allIpV4AddressesThatAreUp);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "All IpV6 Addresses That are up for this machine : ");

        final Vector<String> allIpV6AddressesThatAreUp = WaveNetworkUtils.getAllIpV6AddressesThatAreUpForThisMachine ();

        DebugUtils.prettyPrint (allIpV6AddressesThatAreUp);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "All IpV4 Public Addresses That are up for this machine : ");

        final Vector<String> allIpV4PublicAddressesThatAreUp = WaveNetworkUtils.getAllIpV4PublicAddressesThatAreUpForThisMachine ();

        DebugUtils.prettyPrint (allIpV4PublicAddressesThatAreUp);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "All IpV6 Public Addresses That are up for this machine : ");

        final Vector<String> allIpV6PublicAddressesThatAreUp = WaveNetworkUtils.getAllIpV6PublicAddressesThatAreUpForThisMachine ();

        DebugUtils.prettyPrint (allIpV6PublicAddressesThatAreUp);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "A IPV4 Public Address that is up for this machine : %s", WaveNetworkUtils.getAIpV4PublicAddressThatIsUpForThisMachine ());

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "A IPV6 Public Address that is up for this machine : %s", WaveNetworkUtils.getAIpV6PublicAddressThatIsUpForThisMachine ());

        final LocationId thisLocationId = LocationId.getThisLocationId ();

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "This Location Id : %s", thisLocationId.toString ());

        // DaemonUtils.daemonize ();

        WaveThread.joinAllThreads ();

        WaveAssertUtils.waveAssert ();
    }
}
