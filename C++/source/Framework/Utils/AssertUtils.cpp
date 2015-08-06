/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/TraceUtils.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"

namespace WaveNs
{

void waveAssert (bool isAssertNotRequired, const char *pFileName, UI32 lineNumber)
{
    if (false == isAssertNotRequired)
    {
        (PrismFrameworkObjectManager::getInstance ())->waveAssert (isAssertNotRequired, pFileName, lineNumber);
    }
}

}
