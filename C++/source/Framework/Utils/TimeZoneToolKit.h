/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef TIMEZONETOOLKIT
#define TIMEZONETOOLKIT

#include "Framework/Types/Types.h"
#include "Framework/Types/Date.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include <time.h>

using namespace std;

namespace WaveNs
{

class TimeZoneToolKit
{
    private:
    protected:
    public:
        static void initialize                  ();
        static SI8  getTimeZoneHours            ();
        static void setTimeZoneHours            (const SI8 timeZoneHours);
        static SI8  getTimeZoneMinutes          ();
        static void setTimeZoneMinutes          (const SI8 timeZoneMinutes);
        static char getPostiveNegativeOffset    ();
        static void setPostiveNegativeOffset    (const char postiveNegativeOffset);
        static char getZoneSeperator            ();
        static void setZoneSeperator            (const char zoneSeperator);

       // Now the data members

    private :

        static SI8         s_TimeZoneHours;
        static SI8         s_TimeZoneMinutes;
        static char        s_positiveNegativeOffset;
        static char        s_zoneSeperator;

    protected :
    public :

};

}

#endif // TIMEZONETOOLKIT
