/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/ObjectModel/Rest/WaveObjectModelPlantUmlWaveServerPage.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "HttpInterface/HttpToolKit.h"

namespace WaveNs
{

WaveObjectModelPlantUmlWaveServerPage::WaveObjectModelPlantUmlWaveServerPage ()
    : WaveServerPageForRest (HttpInterfaceReceiverObjectManager::getInstance (), "/Wave/Rest/ObjectModel/plantUml")
{
}

WaveObjectModelPlantUmlWaveServerPage::~WaveObjectModelPlantUmlWaveServerPage ()
{
}

void WaveObjectModelPlantUmlWaveServerPage::requestHandlerForGet (const HttpRequest &httpRequest)
{
    set<string> filters;
    string      ormOutput;
    string      okString;

    OrmRepository::getPlantUmlOrm (filters, ormOutput);

    HttpToolKit::getOkStringWithContentTypeAndLength(okString, "text/plain", ormOutput.size ());

    okString += ormOutput;

    ServerStreamingSocket *pServerStreamingSocket = httpRequest.getPServerStreamingSocket ();

    if (NULL != pServerStreamingSocket)
    {
        (*pServerStreamingSocket) << okString;
    }
}

}
