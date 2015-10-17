/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.TimeZone;

import java.util.Calendar;
import java.util.TimeZone;

import com.CxWave.Wave.Framework.Type.SI8;

public class TimeZoneToolKit
{
    private static SI8      s_timeZoneHours          = new SI8 (0);
    private static SI8      s_timeZoneMinutes        = new SI8 (0);
    private static char     s_positiveNegativeOffset = '+';
    private static char     s_zoneSeparator          = ':';
    private static TimeZone s_defaultTimeZone        = TimeZone.getDefault ();

    private TimeZoneToolKit ()
    {
    }

    public static void initialize ()
    {
        final long offSet = s_defaultTimeZone.getOffset (Calendar.ZONE_OFFSET);
        final long numberOfHoursInOffset = offSet / 1000 / 3600;
        final long numberOfMinutesInOffset = (offSet % 3600000) / 60;

        s_timeZoneHours = new SI8 (numberOfHoursInOffset);
        s_timeZoneMinutes = new SI8 (numberOfMinutesInOffset);

        if (s_timeZoneHours.getValue () > 0)
        {
            s_positiveNegativeOffset = '+';
        }
        else if (((s_timeZoneHours.getValue ()) == 0) && ((s_timeZoneMinutes.getValue ()) > 0))
        {
            s_positiveNegativeOffset = '+';
        }
        else
        {
            s_positiveNegativeOffset = '-';
        }
    }

    public static TimeZone getDefaultTimeZone ()
    {
        return s_defaultTimeZone;
    }

    public static void setDefaultTimeZone (final TimeZone defaultTimeZone)
    {
        s_defaultTimeZone = defaultTimeZone;
    }

    public static SI8 getTimeZoneHours ()
    {
        return s_timeZoneHours;
    }

    public static void setTimeZoneHours (final SI8 timeZoneHours)
    {
        s_timeZoneHours = timeZoneHours;
    }

    public static SI8 getTimeZoneMinutes ()
    {
        return s_timeZoneMinutes;
    }

    public static void setTimeZoneMinutes (final SI8 timeZoneMinutes)
    {
        s_timeZoneMinutes = timeZoneMinutes;
    }

    public static char getPositiveNegativeOffset ()
    {
        return s_positiveNegativeOffset;
    }

    public static void setPositiveNegativeOffset (final char positiveNegativeOffset)
    {
        s_positiveNegativeOffset = positiveNegativeOffset;
    }

    public static char getZoneSeparator ()
    {
        return s_zoneSeparator;
    }

    public static void setZoneSeparator (final char zoneSeparator)
    {
        s_zoneSeparator = zoneSeparator;
    }
}
