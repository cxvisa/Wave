/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPURLCONNECTION_H
#define HTTPURLCONNECTION_H

#include "Framework/Types/Uri.h"

#include <map>
#include <string>

using namespace std;

namespace WaveNs
{

class ClientStreamingSocket;

class HttpUrlConnection
{
    private :
    protected :
    public :
                      HttpUrlConnection (const string &urlString);
        virtual      ~HttpUrlConnection ();

        virtual void  connect           ();

        virtual void  postJson          (const string &jsonContent);

                void  setHeader         (const string &headerName, const string  &headerValue);

        // Now the data members

    private :
        Uri                    m_url;
        map<string, string>    m_headers;
        ClientStreamingSocket *m_pClientStringSocket;

    protected :
    public :
};

}

#endif // HTTPURLCONNECTION_H
