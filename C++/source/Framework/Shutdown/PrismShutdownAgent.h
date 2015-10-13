/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMSHUTDOWNAGENT_H
#define PRISMSHUTDOWNAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class PrismShutdownAgentContext;

class PrismShutdownAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            PrismShutdownAgent                  (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~PrismShutdownAgent                  ();
        virtual ResourceId  execute                             ();

                ResourceId  getListOfEnabledServicesStep        (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  shutdownServicesStep                (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  uninstallServicesStep               (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  uninitializeServicesStep            (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  disableServicesStep                 (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  shutdownPostPhaseServicesStep       (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  uninstallPostPhaseServicesStep      (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  uninitializePostPhaseServicesStep   (PrismShutdownAgentContext *pPrismShutdownAgentContext);
                ResourceId  disablePostPhaseServicesStep        (PrismShutdownAgentContext *pPrismShutdownAgentContext);

                bool        requiresShutdown               (const WaveServiceId &waveServiceId);

    // Now the data members

    private :
        FrameworkSequenceGenerator &m_currentFrameworkSequenceGenerator;

    protected :
    public :
};

}

#endif // PRISMSHUTDOWNAGENT_H
