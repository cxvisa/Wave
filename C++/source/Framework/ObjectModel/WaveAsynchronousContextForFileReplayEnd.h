/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORFILEREPLAYEND_H
#define WAVEASYNCHRONOUSCONTEXTFORFILEREPLAYEND_H

#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForFileReplayEnd: public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForFileReplayEnd (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForFileReplayEnd ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORFILEREPLAYEND_H
