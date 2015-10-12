/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.String;

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
        return (! (isWhiteSpace (inputString)));
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
        return (! (isBlank (inputString)));
    }
}
