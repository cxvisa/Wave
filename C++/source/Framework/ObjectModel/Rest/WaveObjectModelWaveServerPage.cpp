/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/Rest/WaveObjectModelWaveServerPage.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "HttpInterface/HttpToolKit.h"

namespace WaveNs
{

WaveObjectModelWaveServerPage::WaveObjectModelWaveServerPage ()
    : WaveServerPageForRest (HttpInterfaceReceiverObjectManager::getInstance (), "/Wave/Rest/ObjectModel/*")
{
}

WaveObjectModelWaveServerPage::~WaveObjectModelWaveServerPage ()
{
}

void WaveObjectModelWaveServerPage::requestHandlerForGet (const HttpRequest &httpRequest)
{
    const string uri                         = httpRequest.getUri ();
    const string path                        = getPath ();
          string pathWithoutWildCardAtTheEnd = path;

    if (0 != (pathWithoutWildCardAtTheEnd.length ()))
    {
        if ('*' == pathWithoutWildCardAtTheEnd[(pathWithoutWildCardAtTheEnd.length ()) - 1])
        {
            pathWithoutWildCardAtTheEnd.erase (pathWithoutWildCardAtTheEnd.length () - 2);
        }
    }

    trace (TRACE_LEVEL_DEBUG, "WaveObjectModelWaveServerPage::get : Path without Wildcard at the end : \"" + pathWithoutWildCardAtTheEnd + "\"");

    string            adjustedPath         = pathWithoutWildCardAtTheEnd + "/";
    string            adjustedUri          = uri;
    UI32              lengthOfAdjustedPath = adjustedPath.length ();
    string::size_type position             = uri.find (adjustedPath, 0);

    if (string::npos != position)
    {
        adjustedUri.replace (0, lengthOfAdjustedPath, "");
    }

    trace (TRACE_LEVEL_DEBUG, "WaveObjectModelWaveServerPage::get : Adjusted URI : \"" + adjustedUri + "\"");

    vector<WaveManagedObject *> *pQueryResults = querySynchronously (adjustedUri);

    waveAssert (NULL != pQueryResults, __FILE__, __LINE__);

    string                 httpResponse;
    ServerStreamingSocket *pServerStreamingSocket = httpRequest.getPServerStreamingSocket ();

    HttpToolKit::getOkStringForGetForRestJson (httpResponse, "");

    if (NULL != pServerStreamingSocket)
    {
        (*pServerStreamingSocket) << httpResponse;
    }

    UI32 numberOfQueryResults = pQueryResults->size ();
    UI32 i                    = 0;

    (*pServerStreamingSocket) << "{\r\n\"response\" : [\r\n";

    for (i = 0; i < numberOfQueryResults; i++)
    {
        string jsonObjectData;

        WaveManagedObject *pWaveManagedObject = (*pQueryResults)[i];

        waveAssert (NULL != pWaveManagedObject, __FILE__, __LINE__);

        pWaveManagedObject->getJsonObjectData (jsonObjectData);

        (*pServerStreamingSocket) << jsonObjectData;

        if ((numberOfQueryResults - 1) != i)
        {
            (*pServerStreamingSocket) << ",";
        }

        (*pServerStreamingSocket) << "\r\n";
    }

    (*pServerStreamingSocket) << "]\r\n}\r\n";
}

}
