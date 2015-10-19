/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEINITIALIZEWORKERSTARTWAVESERVICESCONTEXT_H
#define WAVEINITIALIZEWORKERSTARTWAVESERVICESCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"
#include "Framework/Core/WaveFrameworkObjectManagerInitializeWorker.h"

namespace WaveNs
{

class WaveBootAgent;

class WaveFrameworkInitializeWorkerStartServicesContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                        WaveFrameworkInitializeWorkerStartServicesContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                       ~WaveFrameworkInitializeWorkerStartServicesContext ();
        void            setWaveBootMode                                   (WaveBootMode waveBootMode);
        WaveBootMode   getWaveBootMode                                   () const;
        void            setWaveBootPhase                                   (const WaveBootPhase &waveBootPhase);
        WaveBootPhase   getWaveBootPhase                                   () const;
        void            setPWaveBootAgent                                 (WaveBootAgent *pWaveBootAgent);
        WaveBootAgent *getPWaveBootAgent                                 ();
        bool            isSchemaChangedOnFwdl                              () const;
        void            setSchemaChangedOnFwdl                             (bool hasChanged);
        bool            getIsSchemaUpgradedSuccessfully                    () const;
        void            setIsSchemaUpgradedSuccessfully                    (const bool &isSchemaUpgradedSuccessfully);

    // Now the data members

    private :
        WaveBootMode   m_waveBootMode;
        WaveBootPhase   m_waveBootPhase;
        WaveBootAgent *m_pWaveBootAgent;
        bool            m_isSchemaChangedOnFwdl;
        bool            m_isSchemaUpgradedSuccessfully;

    protected :
    public :
};

}

#endif // WAVEINITIALIZEWORKERSTARTWAVESERVICESCONTEXT_H
