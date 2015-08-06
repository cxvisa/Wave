/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "License/LicenseObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

LicenseObjectManager::LicenseObjectManager ()
    : WaveObjectManager ("Licnese")
{
}

LicenseObjectManager *LicenseObjectManager::getInstance ()
{
    static LicenseObjectManager *pLicenseObjectManager = NULL;

    if (NULL == pLicenseObjectManager)
    {
        pLicenseObjectManager = new LicenseObjectManager ();
        WaveNs::prismAssert (NULL != pLicenseObjectManager, __FILE__, __LINE__);
    }

    return (pLicenseObjectManager);
}

LicenseObjectManager::~LicenseObjectManager ()
{
}

WaveServiceId LicenseObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

}
