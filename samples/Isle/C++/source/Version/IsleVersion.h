/***************************************************************************
 *   Copyright (C) 2005Vidyasagara Guntaka                                 *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEVERSION_H
#define WAVEVERSION_H

#include <string>
#include "Framework/Utils/StringUtils.h"

using namespace std;

namespace IsleNs
{

class IsleVersion
{
    private :
        IsleVersion ();

    protected :
    public:
                                  ~IsleVersion     ();

                     string        getMajor         () const;
                     string        getMinor         () const;
                     string        getPatch         () const;
                     string        getRevision      () const;
                     string        getBuildType     () const;
                     string        getBuildNumber   () const;
                     string        getDate          () const;
                     string        getUser          () const;
                     string        getHost          () const;
                     string        getDomain        () const;

        static const IsleVersion *getInstance      ();
        static       string        getVersionString ();

    // Now the data members

    private :
        string m_major;
        string m_minor;
        string m_patch;
        string m_revision;
        string m_buildType;
        string m_buildNumber;
        string m_date;
        string m_user;
        string m_host;
        string m_domain;

    protected:
    public:
};

}

#endif // WAVEVERSION_H
