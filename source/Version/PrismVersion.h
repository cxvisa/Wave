/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMVERSION_H
#define PRISMVERSION_H

#include <string>
#include "Framework/Utils/StringUtils.h"

using namespace std;

namespace WaveNs
{

class PrismVersion
{
    private :
        PrismVersion ();

    protected :
    public:
                                  ~PrismVersion     ();

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

        static const PrismVersion *getInstance      ();
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

#endif // PRISMVERSION_H
