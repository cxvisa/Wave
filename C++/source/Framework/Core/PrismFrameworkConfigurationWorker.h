/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKCONFIGURATIONWORKER_H
#define PRISMFRAMEWORKCONFIGURATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/PrismMutex.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"

namespace WaveNs
{

class PrismFrameworkConfigurationContext;

class PrismFrameworkConfigurationWorker : public WaveWorker
{
    private :
        ResourceId validateStep                (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId initializeConfigurationStep (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId saveConfigurationStep       (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId loadConfigurationStep       (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId displayConfigurationStep    (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId sendConfigurationToStandbyStep    (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId resetStartupFileStep              (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId updatePrismConfigurationFileStep  (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        ResourceId setInMemoryConfiguration          (PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext);
        void       setPrismConfigurationValidity     (const bool &validity);
        void       createLockFileForConfigurationFile( ); 
        ResourceId configurationWithFlock ( const UI32 &operationType, PrismFrameworkConfigurationContext *pPrismFrameworkConfigurationContext = NULL);
        void       disableLiveSync                   ();

    protected :
    public :
                            PrismFrameworkConfigurationWorker (WaveObjectManager *pWaveObjectManager);
        virtual            ~PrismFrameworkConfigurationWorker ();
                ResourceId  savePrismConfiguration            (const string &prismConfigurationFile, const bool &syncToStandby);
                ResourceId  loadPrismConfiguration            (const string &prismConfigurationFile);
                bool        getPrismConfigurationValidity     ();
                ResourceId  changePrismConfigurationValidity  (const bool &validity );      
                WaveMessage *createMessageInstance           (const UI32 &operationCode);
                ResourceId  syncPrismConfigurationMessageHandler (FrameworkObjectManagerSyncConfigurationMessage *pFrameworkObjectManagerSyncConfigurationMessage);      

    // Now the data members

    private :
        bool        m_isPrismConfigurationValid ;
        PrismMutex  m_prismConfigurationValidityMutex;
 
    protected :
    public :
};

}

#endif // PRISMFRAMEWORKCONFIGURATIONWORKER_H
