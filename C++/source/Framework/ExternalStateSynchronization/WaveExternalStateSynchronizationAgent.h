/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEEXTERNALSTATESYNCHRONIZATIONAGENT_H
#define WAVEEXTERNALSTATESYNCHRONIZATIONAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class WaveExternalStateSynchronizationAgentContext;

class WaveExternalStateSynchronizationAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            WaveExternalStateSynchronizationAgent      (WaveObjectManager *pWaveObjectManager, UI32 fssStageNumber, ResourceId serviceType);
        virtual            ~WaveExternalStateSynchronizationAgent      ();
        virtual ResourceId  execute                                     ();

                ResourceId  getListOfEnabledServicesStep                (WaveExternalStateSynchronizationAgentContext *pWaveExternalStateSynchronizationAgentContext);
                ResourceId  externalStateSynchronizationServicesStep    (WaveExternalStateSynchronizationAgentContext *pWaveExternalStateSynchronizationAgentContext);

                bool        requiresExternalStateSynchronization        (const WaveServiceId &waveServiceId);

    // Now the data members
    private :
                UI32        m_fssStageNumber;
                ResourceId  m_serviceType;
    protected :
    public :
};

}

#endif // WAVEEXTERNALSTATESYNCHRONIZATIONAGENT_H
