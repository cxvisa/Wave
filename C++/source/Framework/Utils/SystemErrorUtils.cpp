/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/SystemErrorUtils.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

string SystemErrorUtils::getErrorStringForErrorNumber (const SI32 &errorNumber)
{
    static UI32       s_maxBufferSize = 512;
    static char      *s_pBuffer       = new char[s_maxBufferSize + 1];
    static WaveMutex *s_pWaveMutex    = new WaveMutex ();

           string     errorString;

    s_pWaveMutex->lock ();

    char *pErrorBuffer = strerror_r (errorNumber, s_pBuffer, s_maxBufferSize);

    if (NULL != pErrorBuffer)
    {
        s_pBuffer[s_maxBufferSize] = '\0';

        errorString.assign (pErrorBuffer);
    }
    else
    {
        errorString = "E R R O R  O C C U R E D";
    }

    s_pWaveMutex->unlock ();

    return (errorString);
}

}
