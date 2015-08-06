/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORCONFIGREPLAYEND_H
#define WAVEASYNCHRONOUSCONTEXTFORCONFIGREPLAYEND_H

#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForConfigReplayEnd: public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForConfigReplayEnd (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForConfigReplayEnd ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORCONFIGREPLAYEND_H
