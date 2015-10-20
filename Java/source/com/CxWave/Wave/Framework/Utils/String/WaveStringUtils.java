/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.String;

import java.util.Vector;

public class WaveStringUtils
{
    private WaveStringUtils ()
    {
    }

    public static boolean isWhiteSpace (final String inputString)
    {
        if (inputString.matches ("^[\\s]*$"))
        {
            return (true);
        }

        return (false);
    }

    public static boolean isNotWhiteSpace (final String inputString)
    {
        return (!(isWhiteSpace (inputString)));
    }

    public static boolean isBlank (final String inputString)
    {
        if ((null == inputString) || (inputString.isEmpty ()))
        {
            return (true);
        }

        if (isWhiteSpace (inputString))
        {
            return (true);
        }

        return (false);
    }

    public static boolean isNotBlank (final String inputString)
    {
        return (!(isBlank (inputString)));
    }

    public static void tokenize (final String inputString, final Vector<String> tokens, final char separator)
    {
        final int inputLength = inputString.length ();
        int startPosition = 0;
        int endPosition = 0;
        String token;

        tokens.clear ();

        while (startPosition < inputLength)
        {
            endPosition = inputString.indexOf (separator, startPosition);

            if (-1 != endPosition)
            {
                if (endPosition > startPosition)
                {
                    token = inputString.substring (startPosition, endPosition);
                    tokens.add (token);
                }

                startPosition = endPosition + 1;
            }
            else
            {
                token = inputString.substring (startPosition);
                tokens.add (token);
                break;
            }
        }
    }
}
