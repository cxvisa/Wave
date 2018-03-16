/***************************************************************************
 *   Copyright (C) 2005-2018 Vidyasagara Guntaka                          *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Security/Local/SecurityLocalObjectManager.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

SecurityLocalObjectManager::SecurityLocalObjectManager ()
        : WaveLocalObjectManager (getServiceName ())
{
}

SecurityLocalObjectManager::~SecurityLocalObjectManager ()
{
}

string SecurityLocalObjectManager::getServiceName ()
{
    return ("Security Local");
}

SecurityLocalObjectManager *SecurityLocalObjectManager::getInstance ()
{
    static SecurityLocalObjectManager *pSecurityLocalObjectManager = NULL;

    if (NULL == pSecurityLocalObjectManager)
    {
        pSecurityLocalObjectManager = new SecurityLocalObjectManager ();
    }

    WaveNs::waveAssert (NULL != pSecurityLocalObjectManager, __FILE__, __LINE__);

    return (pSecurityLocalObjectManager);
}

}

