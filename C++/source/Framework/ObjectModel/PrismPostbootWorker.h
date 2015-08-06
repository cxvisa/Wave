/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTWORKER_H
#define PRISMPOSTBOOTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class PrismPostbootObjectManagerMessage;

class PrismPostbootWorker : public WaveWorker
{
    private :
                void        postbootHandler                     (PrismPostbootObjectManagerMessage *pPostbootMessage);
                void        postbootBootWorkersStep             (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void        postbootBootWorkersStepCallback     (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase);
                void        postbootBootSelfStep                (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void        postbootBootSelfStepCallback        (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase);

    protected :
    public :
                            PrismPostbootWorker                 (WaveObjectManager *pWaveObjectManager);
        virtual            ~PrismPostbootWorker                 ();

    // Now the data members
    private :
    protected :
    public :
};

}
#endif // PRISMPOSTBOOTWORKER_H
