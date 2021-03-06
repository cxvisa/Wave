/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "Framework/Types/Types.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class ServerStreamingSocket;

class HttpRequest
{
    private :
    protected :
    public :
                                 HttpRequest                (string &httpRequest, ServerStreamingSocket *pServerStreamingSocket = NULL);
                                ~HttpRequest                ();

        WaveHttpInterfaceMethod  getWaveHttpInterfaceMethod () const;
        void                     setWaveHttpInterfaceMethod (const WaveHttpInterfaceMethod &waveHttpInterfaceMethod);

        string                   getUri                     () const;
        void                     setUri                     (const string &uri);

        vector<string>           getUriTokens               () const;
        void                     setUriTokens               (const vector<string> &uriTokens);

        string                   getAuthorizarion           () const;
        void                     setAuthorization           (const string &authorization);

        UI32                     getContentLength           () const;
        void                     setContentLength           (const UI32 &contentLength);

        WaveHttpContentType      getContentType             () const;
        void                     setContentType             (const WaveHttpContentType &contentType);

        string                   getContent                 () const;
        void                     setContent                 (const string &content);

        string                   getContentBoundary         () const;
        void                     setContentBoundary         (const string &contentBoundry);

        UI32                     getNumberOfEntities        () const;
        void                     getEntityAtIndex           (const UI32 &index, string &entityName, string &entityValue, string &entityFileName);

        void                     getEntityValueByName       (const string &entitityName, string &entityValue) const;
        bool                     isAKnownEntity             (const string &entitityName) const;

        ServerStreamingSocket   *getPServerStreamingSocket  () const;

        string                   getHost                    () const;
        void                     setHost                    (const string &host);

        bool                     getIsContentReadIncomplete () const;
        void                     setIsContentReadIncomplete (bool isContentReadIncomplete);

        map<string, string>      getUriParamterValues       () const;
        void                     setUriParamterValues       (const map<string, string> &uriParamterValues);

        void                     getUriParameterValue       (const string &uriParameterName, string &uriParamterValue) const;

    // Now the data members

    private :
               WaveHttpInterfaceMethod m_waveHttpInterfaceMethod;
               string                  m_uri;
               vector<string>          m_uriTokens;
               string                  m_authorization;
               UI32                    m_contentLength;
               WaveHttpContentType     m_contentType;
               string                  m_contentBoundary;
               string                  m_content;
               bool                    m_isContentReadIncomplete;
               vector<string>          m_entityNames;
               vector<string>          m_entityFileNames;
               vector<string>          m_entityValues;
               map<string, string>     m_entitiesMap;
               string                  m_host;
               map<string, string>     m_uriParameterValues;

               ServerStreamingSocket  *m_pServerStreamingSocket;

        static string                  s_authorizationString;
        static string                  s_contentLengthString;
        static string                  s_contentTypeString;
        static string                  s_hostString;

    protected :
    public :
};

}

#endif // HTTPREQUEST_H
