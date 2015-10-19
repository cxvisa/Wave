/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKFAILOVERWORKER_H
#define WAVEFRAMEWORKFAILOVERWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveFrameworkFailoverWorkerContext;
class WaveFrameworkFailoverWorkerSequencerContext;
class WaveFailoverAgentContext;

class WaveFrameworkFailoverWorker : public WaveWorker
{
    private :
    protected :
    public :
                      WaveFrameworkFailoverWorker            (WaveObjectManager *pWaveObjectManager);
        virtual      ~WaveFrameworkFailoverWorker            ();

                void  executeFailover                         (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext);
                void  executeFailoverSelectFailoverAgentStep  (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext);
                void  executeFailoverRunFailoverAgentStep     (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext);
                void  executeFailoverRunFailoverAgentStepCallback (WaveFailoverAgentContext *pWaveFailoverAgentContext);
                void  executeFailoverDestroyFailoverAgentStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext);
                void  executeFailoverCompleteEventStep        (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEFRAMEWORKFAILOVERWORKER_H
