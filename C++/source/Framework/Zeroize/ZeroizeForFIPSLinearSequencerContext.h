/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S                                                  *
 ***************************************************************************/

#ifndef ZEROIZEFORFIPSLINEARSEQUENCERCONTEXT_H
#define ZEROIZEFORFIPSLINEARSEQUENCERCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class ZeroizeForFIPSLinearSequencerContext : public WaveLinearSequencerContext
{
    protected:
    public:
        ZeroizeForFIPSLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        ~ZeroizeForFIPSLinearSequencerContext (); 

        
    // Now the data members

    protected:
    public:
};

}

#endif // ZEROIZEFORFIPSLINEARSEQUENCERCONTEXT_H
