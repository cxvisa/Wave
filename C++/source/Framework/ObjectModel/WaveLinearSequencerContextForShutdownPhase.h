/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/

#ifndef WAVELINEARSEQUENCERCONTEXTFORSHUTDOWNPHASE_H
#define WAVELINEARSEQUENCERCONTEXTFORSHUTDOWNPHASE_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include <map>

namespace WaveNs
{
class UnifiedClientBackendDetails;

class WaveLinearSequencerContextForShutdownPhase : public WaveLinearSequencerContext
{
    private:
    protected:
    public:
                      WaveLinearSequencerContextForShutdownPhase(WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual      ~WaveLinearSequencerContextForShutdownPhase();

                void  setBackendMap(const map<string,UnifiedClientBackendDetails*>  &backendMap);  
                map<string,UnifiedClientBackendDetails*>  getBackendMap() const;

                //data members
    private:
        map<string,UnifiedClientBackendDetails*> m_backendMap;
    protected:
    public:        
};

}

#endif
