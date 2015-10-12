/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Time;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class WaveTimeUtils
{
    private WaveTimeUtils ()
    {
    }

    public static String ctime ()
    {
        LocalDateTime     localDateTime     = LocalDateTime.now ();
        DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern ("EEE MMM dd HH:mm:ss yyyy");
        String            formattedDateTime = localDateTime.format (dateTimeFormatter);

        return (formattedDateTime);
    }
}
