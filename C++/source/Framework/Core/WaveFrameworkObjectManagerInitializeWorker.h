/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKOBJECTMANAGERINITIALIZEWORKER_H
#define WAVEFRAMEWORKOBJECTMANAGERINITIALIZEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Boot/WaveBootAgent.h"
#include "Framework/Utils/WaveMutex.h"
#include "Framework/Postboot/WavePostbootDebug.h"
#include "Framework/ObjectRelationalMapping/DatabaseSchema.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"

namespace WaveNs
{

typedef enum
{
    WAVE_BOOT_UNKNOWN = 0,
    WAVE_BOOT_FIRST_TIME,
    WAVE_BOOT_PERSISTENT,
    WAVE_BOOT_PERSISTENT_WITH_DEFAULT,
    WAVE_BOOT_SECONDARY_CONFIGURE,
    WAVE_BOOT_SECONDARY_UNCONFIGURE,
    WAVE_BOOT_SECONDARY_REJOIN,
    WAVE_BOOT_HASTANDBY,
    WAVE_BOOT_PREPARE_FOR_HA_BOOT
} WaveBootMode;

class WaveFrameworkInitializeWorkerStartServicesContext;

class WaveFrameworkObjectManagerInitializeWorker : public WaveWorker
{
    private :
        ResourceId determineNodeBootModeStep (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext);
        ResourceId chooseABootAgentStep      (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext);
        ResourceId runTheBootAgentStep       (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext);
        ResourceId saveConfigurationStep     (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext);
        ResourceId destroyABootAgentStep     (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext);
        ResourceId informServicesToInitializeBeforeBootComplete (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext);
        ResourceId declareBootCompleteStep   (WaveFrameworkInitializeWorkerStartServicesContext *pWaveFrameworkInitializeWorkerStartServicesContext);

        ResourceId performSchemaConversion             (const WaveFrameworkConfiguration &waveFrameworkConfiguration, bool ignoreConfigFile = false);
    	void	   FrameworkUpdateDatabaseSchema	   (FrameworkObjectManagerUpdateDatabaseSchema *pFrameworkObjectManagerUpdateDatabaseSchema);
        //void       buildDatabaseSchemaInfoRepository   (const WaveFrameworkConfiguration &waveFrameworkConfiguration, ManagedObjectSchemaInfoRepository &moRepository, vector<pair<string, UI32> >&tableClassIdTuples);
        ResourceId buildDatabaseSchemaInfoRepository   (const WaveFrameworkConfiguration &waveFrameworkConfiguration, ManagedObjectSchemaInfoRepository &moRepository);

    protected :
    public :
                           WaveFrameworkObjectManagerInitializeWorker (WaveObjectManager *pWaveObjectManager);
                          ~WaveFrameworkObjectManagerInitializeWorker ();

               ResourceId  startWaveServices                          (const WaveBootMode &prismBootMode = WAVE_BOOT_UNKNOWN, const WaveBootPhase &waveBootPhase = WAVE_BOOT_PHASE_ALL_PHASES);

        static bool        getInitialBootCompleted                     ();
        static void        setInitialBootCompleted                     (const bool &initialBootCompleted);
        static void        setInitialSchemaInfoObjectSaved             (bool schemaInfoObjectSaved);
        static bool        getInitialSchemaInfoObjectSaved             ();

        void               populateSchemaUpgradeTableInDb                           ();
    // Now the data members

    private :
               WaveBootAgent      *m_pWaveBootAgent;
        static bool                 m_initialBootcompleted;
        static WaveMutex           m_initialBootcompletedMutex;
               WavePostbootDebug   m_postbootDebug; // to allow invocation of intialize function
        static bool                 m_initialSchemaInfoObjectSaved;
        static WaveMutex           m_initialSchemaInfoObjectSavedMutex;

    protected :
    public :

    friend class WaveFrameworkObjectManager;
};

}

#endif //WAVEFRAMEWORKOBJECTMANAGERINITIALIZEWORKER_H
