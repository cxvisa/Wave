/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/HttpUrlConnection.h"
#include "Framework/Utils/ClientStreamingSocket.h"
#include "HttpInterface/HttpToolKit.h"

namespace WaveNs
{

HttpUrlConnection::HttpUrlConnection (const string &urlString)
    : m_url                 (urlString),
      m_pClientStringSocket (NULL)
{
}

HttpUrlConnection::~HttpUrlConnection ()
{
    if (NULL != m_pClientStringSocket)
    {
        delete m_pClientStringSocket;
    }
}

void HttpUrlConnection::connect ()
{
    m_pClientStringSocket = new ClientStreamingSocket (m_url.getHost (), m_url.getPort (), 1);
}

void HttpUrlConnection::setHeader (const string &headerName, const string &headerValue)
{
    m_headers[headerName] = headerValue;
}

void HttpUrlConnection::postJson (const string &jsonContent)
{
    string jsonPostString;

    HttpToolKit::getSimpleJsonPostString (jsonPostString, jsonContent, m_url);

    if (NULL != m_pClientStringSocket)
    {
        (*m_pClientStringSocket) << jsonPostString;
    }
}

}
