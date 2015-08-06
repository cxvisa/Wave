/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ASSERT_UTILS
#define ASSERT_UTILS

#include "Framework/Types/Types.h"

namespace WaveNs
{

    void waveAssert (bool isAssertRequired, const char *pFileName, UI32 lineNumber);

}

#endif // ASSERT_UTILS
