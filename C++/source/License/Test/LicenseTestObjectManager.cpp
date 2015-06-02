/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "License/Test/LicenseTestObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

LicenseTestObjectManager::LicenseTestObjectManager ()
    : PrismTestObjectManager ("License Test")
{
}

LicenseTestObjectManager *LicenseTestObjectManager::getInstance ()
{
    static LicenseTestObjectManager *pLicenseTestObjectManager = NULL;

    if (NULL == pLicenseTestObjectManager)
    {
        pLicenseTestObjectManager = new LicenseTestObjectManager ();
        WaveNs::prismAssert (NULL != pLicenseTestObjectManager, __FILE__, __LINE__);
    }

    return (pLicenseTestObjectManager);
}

LicenseTestObjectManager::~LicenseTestObjectManager ()
{
}

PrismServiceId LicenseTestObjectManager::getPrismServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void LicenseTestObjectManager::testRequestHandler (RegressionTestMessage *pMessage)
{
    pMessage->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    reply (pMessage);
}

}
