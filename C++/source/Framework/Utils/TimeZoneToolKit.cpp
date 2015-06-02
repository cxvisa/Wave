/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "Framework/Utils/TimeZoneToolKit.h"

extern long timezone; // specifies offset from UTC in secs

namespace WaveNs
{

SI8         TimeZoneToolKit::s_TimeZoneHours = 0;
SI8         TimeZoneToolKit::s_TimeZoneMinutes = 0;
char        TimeZoneToolKit::s_positiveNegativeOffset = '+';
char        TimeZoneToolKit::s_zoneSeperator = ':' ;

void TimeZoneToolKit::initialize ()
{
    tzset(); // get time zone details in the extern variables above

    s_TimeZoneHours = (timezone / 3600);
    s_TimeZoneMinutes = ((timezone % 3600) / 60);

    if (s_TimeZoneHours > 0)
    {
        s_positiveNegativeOffset = '+';
    }
    else if ((s_TimeZoneHours == 0) && (s_TimeZoneMinutes > 0))
    {
        s_positiveNegativeOffset = '+';
    }
    else
    {
        s_positiveNegativeOffset = '-';
    }

}

SI8  TimeZoneToolKit::getTimeZoneHours () 
{
    return s_TimeZoneHours;
}

void TimeZoneToolKit::setTimeZoneHours (const SI8 timeZoneHours)
{
    s_TimeZoneHours = timeZoneHours;
}

SI8  TimeZoneToolKit::getTimeZoneMinutes ()
{
    return s_TimeZoneMinutes;
}

void TimeZoneToolKit::setTimeZoneMinutes (const SI8 timeZoneMinutes)
{
    s_TimeZoneMinutes = timeZoneMinutes;
}

char TimeZoneToolKit::getPostiveNegativeOffset ()
{
    return s_positiveNegativeOffset;
}

void TimeZoneToolKit::setPostiveNegativeOffset (const char postiveNegativeOffset)
{
    s_positiveNegativeOffset = postiveNegativeOffset;
}

char TimeZoneToolKit::getZoneSeperator ()
{
    return s_zoneSeperator;    
}

void TimeZoneToolKit::setZoneSeperator (const char zoneSeperator)
{
    s_zoneSeperator = zoneSeperator;
}

}
