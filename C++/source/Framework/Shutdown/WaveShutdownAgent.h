/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESHUTDOWNAGENT_H
#define WAVESHUTDOWNAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"

namespace WaveNs
{

class WaveShutdownAgentContext;

class WaveShutdownAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            WaveShutdownAgent                  (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        virtual            ~WaveShutdownAgent                  ();
        virtual ResourceId  execute                             ();

                ResourceId  getListOfEnabledServicesStep        (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  shutdownServicesStep                (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  uninstallServicesStep               (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  uninitializeServicesStep            (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  disableServicesStep                 (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  shutdownPostPhaseServicesStep       (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  uninstallPostPhaseServicesStep      (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  uninitializePostPhaseServicesStep   (WaveShutdownAgentContext *pWaveShutdownAgentContext);
                ResourceId  disablePostPhaseServicesStep        (WaveShutdownAgentContext *pWaveShutdownAgentContext);

                bool        requiresShutdown               (const WaveServiceId &waveServiceId);

    // Now the data members

    private :
        FrameworkSequenceGenerator &m_currentFrameworkSequenceGenerator;

    protected :
    public :
};

}

#endif // WAVESHUTDOWNAGENT_H
