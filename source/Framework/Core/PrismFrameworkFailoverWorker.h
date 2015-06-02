/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKFAILOVERWORKER_H
#define PRISMFRAMEWORKFAILOVERWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class PrismFrameworkFailoverWorkerContext;
class PrismFrameworkFailoverWorkerSequencerContext;
class PrismFailoverAgentContext;

class PrismFrameworkFailoverWorker : public WaveWorker
{
    private :
    protected :
    public :
                      PrismFrameworkFailoverWorker            (WaveObjectManager *pWaveObjectManager);
        virtual      ~PrismFrameworkFailoverWorker            ();

                void  executeFailover                         (PrismFrameworkFailoverWorkerContext *pPrismFrameworkFailoverWorkerContext);
                void  executeFailoverSelectFailoverAgentStep  (PrismFrameworkFailoverWorkerSequencerContext *pPrismFrameworkFailoverWorkerSequencerContext);
                void  executeFailoverRunFailoverAgentStep     (PrismFrameworkFailoverWorkerSequencerContext *pPrismFrameworkFailoverWorkerSequencerContext);
                void  executeFailoverRunFailoverAgentStepCallback (PrismFailoverAgentContext *pPrismFailoverAgentContext);
                void  executeFailoverDestroyFailoverAgentStep (PrismFrameworkFailoverWorkerSequencerContext *pPrismFrameworkFailoverWorkerSequencerContext);
                void  executeFailoverCompleteEventStep        (PrismFrameworkFailoverWorkerSequencerContext *pPrismFrameworkFailoverWorkerSequencerContext);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMFRAMEWORKFAILOVERWORKER_H
