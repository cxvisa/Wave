/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney, Amit Agrawal                              *
 ***************************************************************************/

#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class DateTime
{

    private:
    protected:
    public:
                        DateTime                        ();
                        DateTime                        (const string &datetimeInStringFormat);
                        DateTime                        (const time_t &datetimeInTimeT);
                        DateTime                        (const DateTime &datetime);
                       ~DateTime                        ();
                                                      
        string          toString                        ()                                                       const;
        void            fromString                      (const string &datetimeInStringFormat);
        ResourceId      loadFromPlainString             (const string &datetimeInStringFormat);
        void            fromTimeT                       (const time_t &datetimeInTimeT);
                                                       
        bool            operator ==                     (const DateTime &datetime)                               const;
        bool            operator !=                     (const DateTime &datetime)                               const;
        DateTime        &operator =                     (const DateTime &datetime);
                                                       
        UI8             getMonth                        ()                                                       const;
        UI8             getDay                          ()                                                       const;
        SI16            getYear                         ()                                                       const;
        UI8             getHour                         ()                                                       const;
        UI8             getMin                          ()                                                       const;
        UI8             getSec                          ()                                                       const;
        UI32            getMicro                        ()                                                       const;
        SI8             getTimezoneHours                ()                                                       const;
        SI8             getTimezoneMinutes              ()                                                       const;
        void            setAllValues                    (SI16 year, UI8 month, UI8 day, UI8 hour, UI8 min, UI8 sec, UI32 micro, SI8 timezone, SI8 timezoneminutes);
        UI64            getUI64Representation           ();
        string          getPlainString                  ()                                                       const;

    // Now the data members
    private:
        UI8         m_Month;
        UI8         m_Day;
        SI16        m_Year;
        UI8         m_Hour;
        UI8         m_Min;
        UI8         m_Sec;
        UI32        m_Micro;
        SI8         m_TimezoneHours;
        SI8         m_TimezoneMinutes;
        char        m_positiveNegativeOffset; // denotes + or - from UTC offset
        char        m_dateSeperator;
        char        m_timeSeperator;
        char        m_microSeperator;
        char        m_zoneSeperator;
        char        m_betweenDateTime; // denotes 'T'
    protected:
    public:
};

}

#endif //DATETIME_H
