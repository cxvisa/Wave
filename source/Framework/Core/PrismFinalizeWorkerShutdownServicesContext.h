/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#ifndef PRISMFINALIZEWORKERSHUTDOWNSERVICESCONTEXT_H
#define PRISMFINALIZEWORKERSHUTDOWNSERVICESCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Framework/Shutdown/PrismFinalizeWorker.h"

namespace WaveNs
{

class PrismFinalizeWorkerShutdownServicesContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                        PrismFinalizeWorkerShutdownServicesContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                       ~PrismFinalizeWorkerShutdownServicesContext ();
        void                setPrismShutdownMode                               (const PrismShutdownMode &prismShutdownMode);
        PrismShutdownMode   getPrismShutdownMode                               () const;

    // Now the data members

    private :
        PrismShutdownMode   m_prismShutdownMode;

    protected :
    public :
};

}

#endif // PRISMFINALIZEWORKERSHUTDOWNSERVICESCONTEXT_H
