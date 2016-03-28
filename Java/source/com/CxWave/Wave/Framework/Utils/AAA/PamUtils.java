/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.AAA;

import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

public class PamUtils
{
    native static boolean authenticateUsingWaveCpp (final String authenticatonService, final String userName, final String password);

    private static boolean s_authenticationAvailable = false;

    static
    {
        try
        {
            System.loadLibrary ("rt");
            System.loadLibrary ("nsl");
            // System.loadLibrary ("m");
            System.loadLibrary ("uuid");
            System.loadLibrary ("crypto");
            System.loadLibrary ("pam");
            System.loadLibrary ("idn");
            System.loadLibrary ("ssl");
            System.loadLibrary ("xerces-c");
            System.loadLibrary ("xalan-c");
            System.loadLibrary ("xalanMsg");
            System.loadLibrary ("z");
            System.loadLibrary ("pq");
            System.loadLibrary ("Wave");
            System.loadLibrary ("WaveJavaToC++Bridge");

            s_authenticationAvailable = true;
        }
        catch (final Exception e)
        {
            s_authenticationAvailable = false;

            WaveTraceUtils.errorTracePrintf ("PamUtils.static : Wave C++ libraries could not be loaded.  Details : %s", e.toString ());
        }
    }

    public static boolean authenticate (final String authenticatonService, final String userName, final String password)
    {
        if (!s_authenticationAvailable)
        {
            WaveTraceUtils.errorTracePrintf ("PamUtils.authenticate : Wave C++ libraries could not be loaded.  Authentication is not possible.");

            return (false);
        }

        final boolean authenticationResult = authenticateUsingWaveCpp (authenticatonService, userName, password);

        return (authenticationResult);
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Authenticates using given service, username and password.")
    public static void authenticate (final Vector<String> arguments)
    {
        if (3 <= (arguments.size ()))
        {
            final boolean successfullyAuthenticated = authenticate (arguments.get (0), arguments.get (1), arguments.get (2));

            if (successfullyAuthenticated)
            {
                WaveTraceUtils.successTracePrintf ("PamUtils.authenticate : Authentication Successful.");
            }
            else
            {
                WaveTraceUtils.errorTracePrintf ("PamUtils.authenticate : Authentication failed.");
            }
        }
    }
}
