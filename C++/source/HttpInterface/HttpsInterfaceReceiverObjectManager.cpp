/**************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/HttpsInterfaceReceiverObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

HttpsInterfaceReceiverObjectManager::HttpsInterfaceReceiverObjectManager ()
    : HttpInterfaceReceiverObjectManager (getServiceName ())
{
}

HttpsInterfaceReceiverObjectManager::~HttpsInterfaceReceiverObjectManager ()
{
}

string HttpsInterfaceReceiverObjectManager::getServiceName ()
{
    return ("HTTPS Interface");
}

HttpsInterfaceReceiverObjectManager *HttpsInterfaceReceiverObjectManager::getInstance ()
{
    static HttpsInterfaceReceiverObjectManager *pHttpsInterfaceReceiverObjectManager = new HttpsInterfaceReceiverObjectManager ();

    WaveNs::waveAssert (NULL != pHttpsInterfaceReceiverObjectManager, __FILE__, __LINE__);

    return (pHttpsInterfaceReceiverObjectManager);
}

bool HttpsInterfaceReceiverObjectManager::getIsTranportSecurityEnabled () const
{
    return (true);
}

SI32 HttpsInterfaceReceiverObjectManager::getInterfaceReceiverPort () const
{
    return (FrameworkToolKit::getHttpsInterfaceReceiverPort ());
}

}
