/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/ObjectModel/Rest/WaveObjectModelDotGraphWaveServerPage.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "HttpInterface/HttpToolKit.h"

namespace WaveNs
{

WaveObjectModelDotGraphWaveServerPage::WaveObjectModelDotGraphWaveServerPage ()
    : WaveServerPageForRest (HttpInterfaceReceiverObjectManager::getInstance (), "/Wave/Rest/ObjectModel/dotGraph")
{
}

WaveObjectModelDotGraphWaveServerPage::~WaveObjectModelDotGraphWaveServerPage ()
{
}

void WaveObjectModelDotGraphWaveServerPage::requestHandlerForGet (const HttpRequest &httpRequest)
{
    set<string> filters;
    string      ormOutput;
    string      okString;

    OrmRepository::getDotGraphOrm (filters, ormOutput);

    HttpToolKit::getOkStringWithContentTypeAndLength(okString, "text/plain", ormOutput.size ());

    okString += ormOutput;

    ServerStreamingSocket *pServerStreamingSocket = httpRequest.getPServerStreamingSocket ();

    if (NULL != pServerStreamingSocket)
    {
        (*pServerStreamingSocket) << okString;
    }
}

}
