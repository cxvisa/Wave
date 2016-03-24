/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Base64;

import java.util.Vector;

import javax.xml.bind.DatatypeConverter;

import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

public class Base64Utils
{
    public static String decode (final String input)
    {
        final byte[] outputBytes = DatatypeConverter.parseBase64Binary (input);

        final String output = new String (outputBytes);

        return (new String (output));
    }

    public static String encode (final String input)
    {
        final byte[] inputBytes = input.getBytes ();

        final String output = DatatypeConverter.printBase64Binary (inputBytes);

        return (output);
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Encodes a given String using Base64.")
    public static void encodeUsingBase64 (final Vector<String> arguments)
    {
        for (final String argument : arguments)
        {
            WaveTraceUtils.infoTracePrintf ("Encoded String : \"%s\"", encode (argument));
        }
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Decodes a given String using Base64.")
    public static void decodeUsingBase64 (final Vector<String> arguments)
    {
        for (final String argument : arguments)
        {
            WaveTraceUtils.infoTracePrintf ("Decoded String : \"%s\"", decode (argument));
        }
    }
}
