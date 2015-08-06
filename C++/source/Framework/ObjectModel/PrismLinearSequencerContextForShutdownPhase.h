/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/

#ifndef PRISMLINEARSEQUENCERCONTEXTFORSHUTDOWNPHASE_H
#define PRISMLINEARSEQUENCERCONTEXTFORSHUTDOWNPHASE_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include <map>

namespace WaveNs
{
class UnifiedClientBackendDetails;

class PrismLinearSequencerContextForShutdownPhase : public PrismLinearSequencerContext
{
    private:
    protected:
    public:
                      PrismLinearSequencerContextForShutdownPhase(PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual      ~PrismLinearSequencerContextForShutdownPhase();

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
