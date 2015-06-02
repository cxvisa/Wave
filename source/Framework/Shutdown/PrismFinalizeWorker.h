/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFINALIZEWORKER_H
#define PRISMFINALIZEWORKER_H

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
} PrismShutdownMode;

class PrismShutdownAgent;
class PrismFinalizeWorkerShutdownServicesContext;

class PrismFinalizeWorker : protected WaveWorker
{
    private :
        ResourceId chooseAShutdownAgentStep      (PrismFinalizeWorkerShutdownServicesContext *pPrismFinalizeWorkerShutdownServicesContext);
        ResourceId runTheShutdownAgentStep       (PrismFinalizeWorkerShutdownServicesContext *pPrismFinalizeWorkerShutdownServicesContext);
        ResourceId destroyAShutdownAgentStep     (PrismFinalizeWorkerShutdownServicesContext *pPrismFinalizeWorkerShutdownServicesContext);

    protected :
    public :
                            PrismFinalizeWorker   (WaveObjectManager *pWaveObjectManager);
                virtual    ~PrismFinalizeWorker   ();
                ResourceId  shutdownPrismServices (const PrismShutdownMode &prismShutdownMode = WAVE_SHUTDOWN_SECONDARY_CONFIGURE);

    // Now the data members

    private :
        PrismShutdownAgent  *m_pPrismShutdownAgent;

    protected :
    public :
};

}

#endif // PRISMFINALIZEWORKER_H
