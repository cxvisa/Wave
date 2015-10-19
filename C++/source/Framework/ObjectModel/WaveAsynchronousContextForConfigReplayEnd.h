/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORCONFIGREPLAYEND_H
#define WAVEASYNCHRONOUSCONTEXTFORCONFIGREPLAYEND_H

#include "Framework/Utils/WaveAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForConfigReplayEnd: public WaveAsynchronousContext
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForConfigReplayEnd (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForConfigReplayEnd ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORCONFIGREPLAYEND_H
