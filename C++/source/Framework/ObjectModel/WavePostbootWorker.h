/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTWORKER_H
#define WAVEPOSTBOOTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WavePostbootObjectManagerMessage;

class WavePostbootWorker : public WaveWorker
{
    private :
                void        postbootHandler                     (WavePostbootObjectManagerMessage *pPostbootMessage);
                void        postbootBootWorkersStep             (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void        postbootBootWorkersStepCallback     (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase);
                void        postbootBootSelfStep                (WaveLinearSequencerContext *pWaveLinearSequencerContext);
                void        postbootBootSelfStepCallback        (WaveAsynchronousContextForPostbootPhase *pWaveAsynchronousContextForPostbootPhase);

    protected :
    public :
                            WavePostbootWorker                 (WaveObjectManager *pWaveObjectManager);
        virtual            ~WavePostbootWorker                 ();

    // Now the data members
    private :
    protected :
    public :
};

}
#endif // WAVEPOSTBOOTWORKER_H
