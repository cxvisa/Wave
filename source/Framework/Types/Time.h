/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney, Amit Agrawal                              *
 ***************************************************************************/

#ifndef TIME_H
#define TIME_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class Time
{

    private:
    protected:
    public:
                Time        ();
                Time        (const string &timeInStringFormat);
                Time        (const Time &time);
                Time        (const struct tm *ptime);
               ~Time        ();

        string  toString    ()                                  const;
        void    fromString  (const string &timeInStringFormat);

        bool    operator == (const Time &ptime)                 const;
        bool    operator != (const Time &ptime)                 const;
        Time    &operator = (const Time &ptime);

        UI8     getHour()                                       const;
        UI8     getMin()                                        const;
        UI8     getSec()                                        const;
        UI32    getMicro()                                      const;
        SI8     getTimezoneHours()                              const;
        SI8     getTimezoneMinutes()                            const;
        void    setAllValues(UI8 hour, UI8 min, UI8 sec, UI32 micro, SI8 timezone, SI8 timezoneminutes);
        string  getPlainString          () const;

    // Now the data members
    private:
            UI8         m_Hour;
            UI8         m_Min;
            UI8         m_Sec;
            UI32        m_Micro;
            SI8         m_TimezoneHours;
            SI8         m_TimezoneMinutes;
            char        m_positiveNegativeOffset; // denotes + or - from UTC offset
            char        m_timeSeperator;
            char        m_microSeperator;
            char        m_zoneSeperator;
    protected:
    public:
};

}

#endif // TIME_H
