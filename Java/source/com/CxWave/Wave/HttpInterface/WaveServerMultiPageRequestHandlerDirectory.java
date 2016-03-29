/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveServerMultiPageRequestHandlerDirectory
{
    Map<String, WaveServerMultiPageRequestHandler>  m_serverMultiPageRequestHandlerMap               = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    WaveServerMultiPageRequestHandlerDirectoryEntry m_waveServerMultiPageRequestHandlerDirectoryRoot = new WaveServerMultiPageRequestHandlerDirectoryEntry ("/", null);

    public WaveServerMultiPageRequestHandlerDirectory ()
    {
    }

    public boolean isAKnownServerMultiPageRequestHandler (final String path)
    {
        return (m_serverMultiPageRequestHandlerMap.containsKey (path));
    }

    public void registerServerMultiPageRequestHandler (final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        WaveAssertUtils.waveAssert (null != waveServerMultiPageRequestHandler);

        final String path = waveServerMultiPageRequestHandler.getRelativePath ();
        final boolean isAnExistingPage = isAKnownServerMultiPageRequestHandler (path);

        m_waveServerMultiPageRequestHandlerDirectoryRoot.addSibling (path, waveServerMultiPageRequestHandler);

        if (true == isAnExistingPage)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveServerMultiPageRequestHandlerDirectory.registerServerMultiPageRequestHandler : A Request Handler with the path \"%s\" has already been registered.", path);

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            if (null != waveServerMultiPageRequestHandler)
            {
                WaveTraceUtils.develTracePrintf ("WaveServerMultiPageRequestHandlerDirectory.registerServerMultiPageRequestHandler : Registering a Wave Server Multi Page Request Handler : \"%s\"", path);

                m_serverMultiPageRequestHandlerMap.put (path, waveServerMultiPageRequestHandler);
            }
        }
    }

    public void registerServerMultiPageRequestHandler (final String path, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        final boolean isAnExistingPage = isAKnownServerMultiPageRequestHandler (path);

        m_waveServerMultiPageRequestHandlerDirectoryRoot.addSibling (path, waveServerMultiPageRequestHandler);

        if (true == isAnExistingPage)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveServerMultiPageRequestHandlerDirectory.registerServerMultiPageRequestHandler : A Request Handler with the path \"%s\" has already been registered.", path);

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            if (null != waveServerMultiPageRequestHandler)
            {
                WaveTraceUtils.develTracePrintf ("WaveServerMultiPageRequestHandlerDirectory.registerServerMultiPageRequestHandler : Registering a Wave Server Multi Page Request Handler : \"%s\"", path);

                m_serverMultiPageRequestHandlerMap.put (path, waveServerMultiPageRequestHandler);
            }
        }
    }

    public WaveServerMultiPageRequestHandler getWaveServerMultiPageRequestHandler (final String path)
    {
        return (m_waveServerMultiPageRequestHandlerDirectoryRoot.getWaveServerMultiPageRequestHandlerForRelativePath (path));
    }

    // @ShellCommand (shell = ShellDebug.class, briefHelp = "Prints Wave Server Multi Page Request Handler Tree")
    public void printWaveServerMultiPageRequestHandlerTree (final Vector<String> arguments)
    {
        m_waveServerMultiPageRequestHandlerDirectoryRoot.print ();
    }
}
