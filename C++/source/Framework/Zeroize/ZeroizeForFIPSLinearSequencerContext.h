/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S                                                  *
 ***************************************************************************/

#ifndef ZEROIZEFORFIPSLINEARSEQUENCERCONTEXT_H
#define ZEROIZEFORFIPSLINEARSEQUENCERCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class ZeroizeForFIPSLinearSequencerContext : public PrismLinearSequencerContext
{
    protected:
    public:
        ZeroizeForFIPSLinearSequencerContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        ~ZeroizeForFIPSLinearSequencerContext (); 

        
    // Now the data members

    protected:
    public:
};

}

#endif // ZEROIZEFORFIPSLINEARSEQUENCERCONTEXT_H
