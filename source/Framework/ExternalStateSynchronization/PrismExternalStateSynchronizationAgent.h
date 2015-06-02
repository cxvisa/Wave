/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef PRISMEXTERNALSTATESYNCHRONIZATIONAGENT_H
#define PRISMEXTERNALSTATESYNCHRONIZATIONAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class PrismExternalStateSynchronizationAgentContext;

class PrismExternalStateSynchronizationAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            PrismExternalStateSynchronizationAgent      (WaveObjectManager *pWaveObjectManager, UI32 fssStageNumber, ResourceId serviceType);
        virtual            ~PrismExternalStateSynchronizationAgent      ();
        virtual ResourceId  execute                                     ();

                ResourceId  getListOfEnabledServicesStep                (PrismExternalStateSynchronizationAgentContext *pPrismExternalStateSynchronizationAgentContext);
                ResourceId  externalStateSynchronizationServicesStep    (PrismExternalStateSynchronizationAgentContext *pPrismExternalStateSynchronizationAgentContext);

                bool        requiresExternalStateSynchronization        (const PrismServiceId &prismServiceId);

    // Now the data members
    private :
                UI32        m_fssStageNumber;
                ResourceId  m_serviceType;
    protected :
    public :
};

}

#endif // PRISMEXTERNALSTATESYNCHRONIZATIONAGENT_H
