/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/HttpInterfaceGetWorker.h"
#include "HttpToolKit.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include <Framework/Utils/Integer.h>
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include <algorithm>
#include "WaveServerPage.h"
#include "WaveServerPageDirectory.h"
#include "Framework/Utils/TraceUtils.h"

using namespace std;

namespace WaveNs
{

HttpInterfaceGetWorker::HttpInterfaceGetWorker (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager)
    : HttpInterfaceMethodWorker(pHttpInterfaceReceiverObjectManager, WAVE_HTTP_INTERFACE_METHOD_GET)
{
}

HttpInterfaceGetWorker::~HttpInterfaceGetWorker ()
{
}

void HttpInterfaceGetWorker::process (const HttpRequest &httpRequest)
{
    string                 uri                    = httpRequest.getUri                         ();
    WaveServerPage        *pWaveServerPage        = WaveServerPageDirectory::getWaveServerPage (uri);
    ServerStreamingSocket *pServerStreamingSocket = httpRequest.getPServerStreamingSocket      ();

    if (NULL == pWaveServerPage)
    {
        string httpResponse;

        trace (TRACE_LEVEL_DEBUG, "HttpInterfaceGetWorker::process : There is no page registered with the given path \"" + uri + "\"");

        HttpToolKit::getNotFoundErrorString (httpResponse);

        if (NULL != pServerStreamingSocket)
        {
            (*pServerStreamingSocket) << httpResponse;
        }
    }
    else
    {
        trace (TRACE_LEVEL_DEBUG, "HttpInterfaceGetWorker::process : Serving get for \"" + uri + "\"");

        pWaveServerPage->get (httpRequest);
    }
}

}
