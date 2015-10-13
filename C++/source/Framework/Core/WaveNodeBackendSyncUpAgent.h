/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef WAVEBACKENDSYNCUPAGENT_H
#define WAVEBACKENDSYNCUPAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveLinearSequencerContext;

class WaveNodeBackendSyncUpAgent: protected WaveWorker
{
    private :
    protected :
    public :
                            WaveNodeBackendSyncUpAgent           (WaveObjectManager *pWaveObjectManager);
        virtual            ~WaveNodeBackendSyncUpAgent           ();
        virtual ResourceId  execute                              ();

                ResourceId  sendBackendSyncUpStep                (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

                bool        requiresBackendSyncUpNotification    (const WaveServiceId &waveServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif //WAVEBACKENDSYNCUPAGENT_H
