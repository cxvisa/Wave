/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

public class WaveServerPageDirectory
{
    static Map<String, WaveServerPage>  m_serverPageMap;
    static WaveServerPageDirectoryEntry m_waveServerPageDirectoryRoot = new WaveServerPageDirectoryEntry ("/", null);

    public static boolean isAKnownServerPage (final String path)
    {
        return (m_serverPageMap.containsKey (path));
    }

    public static void registerServerPage (final WaveServerPage waveServerPage)
    {
        WaveAssertUtils.waveAssert (null != waveServerPage);

        final String path = waveServerPage.getPath ();
        final boolean isAnExistingPage = isAKnownServerPage (path);

        m_waveServerPageDirectoryRoot.addSibling (path, waveServerPage);

        if (true == isAnExistingPage)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveServerPageDirectory.registerServerPage : A Page with the path \"%s\" has already been registered.", path);

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            if (null != waveServerPage)
            {
                WaveTraceUtils.develTracePrintf ("WaveServerPageDirectory.registerServerPage : Registering a Wave Server Page : \"%s\"", path);

                m_serverPageMap.put (path, waveServerPage);
            }
        }
    }

    public static void registerServerPage (final String path, final WaveServerPage waveServerPage)
    {
        final boolean isAnExistingPage = isAKnownServerPage (path);

        m_waveServerPageDirectoryRoot.addSibling (path, waveServerPage);

        if (true == isAnExistingPage)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveServerPageDirectory::registerServerPage : A Page with the path \"%s\" has already been registered.", path);

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            if (null != waveServerPage)
            {
                WaveTraceUtils.develTracePrintf ("WaveServerPageDirectory.registerServerPage : Registering a Wave Server Page : \"%s\"", path);

                m_serverPageMap.put (path, waveServerPage);
            }
        }
    }

    public static WaveServerPage getWaveServerPage (final String path)
    {
        return (m_waveServerPageDirectoryRoot.getWaveServerPageForRelativePath (path));
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Prints Wave Server Page Tree")
    public static void printWaveServerPageTree (final Vector<String> arguments)
    {
        m_waveServerPageDirectoryRoot.print ();
    }
}
