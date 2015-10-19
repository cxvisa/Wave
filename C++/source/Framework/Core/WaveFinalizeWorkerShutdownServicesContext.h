/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Geetha Aparna                                                *
 ***************************************************************************/

#ifndef WAVEFINALIZEWORKERSHUTDOWNSERVICESCONTEXT_H
#define WAVEFINALIZEWORKERSHUTDOWNSERVICESCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "Framework/Shutdown/WaveFinalizeWorker.h"

namespace WaveNs
{

class WaveFinalizeWorkerShutdownServicesContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                        WaveFinalizeWorkerShutdownServicesContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                       ~WaveFinalizeWorkerShutdownServicesContext ();
        void                setWaveShutdownMode                               (const WaveShutdownMode &waveShutdownMode);
        WaveShutdownMode   getWaveShutdownMode                               () const;

    // Now the data members

    private :
        WaveShutdownMode   m_waveShutdownMode;

    protected :
    public :
};

}

#endif // WAVEFINALIZEWORKERSHUTDOWNSERVICESCONTEXT_H
