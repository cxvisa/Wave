/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/WaveServerPageForRest.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "HttpToolKit.h"

namespace WaveNs
{

WaveServerPageForRest::WaveServerPageForRest (HttpInterfaceReceiverObjectManager *pHttpInterfaceReceiverObjectManager, const string &path)
    : WaveServerPage (pHttpInterfaceReceiverObjectManager, path)
{
}

WaveServerPageForRest::~WaveServerPageForRest ()
{
}

void WaveServerPageForRest::get (const HttpRequest &httpRequest)
{
    requestHandlerForGet (httpRequest);
}

void WaveServerPageForRest::requestHandlerForGet (const HttpRequest &httpRequest)
{
    string                 httpResponse;
    ServerStreamingSocket *pServerStreamingSocket = httpRequest.getPServerStreamingSocket ();

    HttpToolKit::getOkStringForGetForRestXml (httpResponse, "");

    if (NULL != pServerStreamingSocket)
    {
        (*pServerStreamingSocket) << httpResponse;
    }
}

}
