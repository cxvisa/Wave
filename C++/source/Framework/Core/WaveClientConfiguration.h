/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVECLIENTCONFIGURATION_H
#define WAVECLIENTCONFIGURATION_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveClientConfiguration
{
    private :
    protected :
    public :
                WaveClientConfiguration   ();
               ~WaveClientConfiguration   ();

        string  getApplicationName        () const;
        void    setApplicationName        (const string &applicationName);

        bool    getIsADaemon              () const;
        void    setIsADaemon              (const bool &isADaemon);

        bool    getIsSysLogRequired       () const;
        void    setIsSysLogRequired       (const bool &isSysLogRequired);

        bool    getIsDatabaseEnabled      () const;
        void    setIsDatabaseEnabled      (const bool &isDatabaseenabled);

        SI32    getDatabasePort           () const;
        void    setDatabasePort           (const SI32 &databasePort);

        bool    getNeedShell              () const;
        void    setNeedShell              (const bool &needShell);

        string  getApplicationCompactName () const;

    // Now the data members

    private :
        string m_applicationName;
        bool   m_isADaemon;
        bool   m_isSysLogRequired;
        bool   m_isDatabaseEnabled;
        SI32   m_databasePort;
        bool   m_needShell;

    protected :
    public :
};

}

#endif //WAVECLIENTCONFIGURATION_H
