/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFINALIZEWORKER_H
#define WAVEFINALIZEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
namespace WaveNs
{

// Services shutdown steps will be based on the operation.
typedef enum
{
    WAVE_SHUTDOWN_SECONDARY_CONFIGURE = 0,
    WAVE_SHUTDOWN_SECONDARY_REJOIN,
    WAVE_SHUTDOWN_SECONDARY_ROLLBACK,
    WAVE_SHUTDOWN_STANDBY_CONFIGURE
} WaveShutdownMode;

class WaveShutdownAgent;
class WaveFinalizeWorkerShutdownServicesContext;

class WaveFinalizeWorker : protected WaveWorker
{
    private :
        ResourceId chooseAShutdownAgentStep      (WaveFinalizeWorkerShutdownServicesContext *pWaveFinalizeWorkerShutdownServicesContext);
        ResourceId runTheShutdownAgentStep       (WaveFinalizeWorkerShutdownServicesContext *pWaveFinalizeWorkerShutdownServicesContext);
        ResourceId destroyAShutdownAgentStep     (WaveFinalizeWorkerShutdownServicesContext *pWaveFinalizeWorkerShutdownServicesContext);

    protected :
    public :
                            WaveFinalizeWorker   (WaveObjectManager *pWaveObjectManager);
                virtual    ~WaveFinalizeWorker   ();
                ResourceId  shutdownWaveServices (const WaveShutdownMode &waveShutdownMode = WAVE_SHUTDOWN_SECONDARY_CONFIGURE);

    // Now the data members

    private :
        WaveShutdownAgent  *m_pWaveShutdownAgent;

    protected :
    public :
};

}

#endif // WAVEFINALIZEWORKER_H
