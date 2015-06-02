/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

/***************************************************************************
 *   The contents of this file have been modeled after the following       *
 *   RFC 2396 (www.ietf.org/rfc/rfc2396.txtRFC 2396)                       *
 *   Please refer to Java URI Class For more information                   *
 *       (http://docs.oracle.com/javase/6/docs/api/java/net/URI.html)      *
 ***************************************************************************/

#ifndef URI_H
#define URI_H

#include "Framework/Types/Types.h"

#include <string>

using namespace std;

namespace WaveNs
{

class Uri
{
    private:
        void computeAuthority          ();
        void computeSchemeSpecificPart ();
        void invalidate                ();
        void computeFlags              ();
        void parseSchemeSpecificPart   ();
        void parseAuthority            ();

    protected :
    public :
                Uri                   ();
                Uri                   (const string &uriString);
                Uri                   (const string &scheme, const string &schemeSpecificPart, const string &fragment);
                Uri                   (const string &scheme, const string userInformation, const string &host, const SI32 &port, const string &path, const string &query, const string &fragment);
                Uri                   (const string &scheme, const string &host, const string &path, const string &fragment);
                Uri                   (const string &scheme, const string &authority, const string &path, const string &query, const string &fragment);
                Uri                   (const Uri &thatUri);

               ~Uri                   ();

        Uri    &operator =            (const Uri &thatUri);
        bool    operator ==           (const Uri &thatUri);

        void    fromString            (const string &uriString);
        void    toString              (string &uriString) const;

        string  getScheme             () const;
        string  getSchemeSpecificPart () const;
        string  getAuthority          () const;
        string  getUserInformation    () const;
        string  getHost               () const;
        SI32    getPort               () const;
        string  getPath               () const;
        string  getQuery              () const;
        string  getFragment           () const;

        bool    getIsOpaque           () const;
        bool    getIsHierarchical     () const;
        bool    getIsAbsolute         () const;
        bool    getIsValid            () const;

        void    print                 () const;

    // Now the Data Members

    private :
        string m_scheme;
        string m_schemeSpecificPart;
        string m_authority;
        string m_userInformation;
        string m_host;
        SI32   m_port;
        string m_path;
        string m_query;
        string m_fragment;

        bool   m_isHierarchical;
        bool   m_isOpaque;
        bool   m_isAbsolute;
        bool   m_isValid;

    protected :
    public :
};

}

#endif // URI_H
