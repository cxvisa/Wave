/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKCONFIGURATIONWORKER_H
#define PRISMFRAMEWORKCONFIGURATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/WaveMutex.h"
#include "Framework/Core/FrameworkObjectManagerMessages.h"

namespace WaveNs
{

class WaveFrameworkConfigurationContext;

class WaveFrameworkConfigurationWorker : public WaveWorker
{
    private :
        ResourceId validateStep                (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId initializeConfigurationStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId saveConfigurationStep       (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId loadConfigurationStep       (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId displayConfigurationStep    (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId sendConfigurationToStandbyStep    (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId resetStartupFileStep              (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId updatePrismConfigurationFileStep  (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId setInMemoryConfiguration          (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        void       setPrismConfigurationValidity     (const bool &validity);
        void       createLockFileForConfigurationFile( ); 
        ResourceId configurationWithFlock ( const UI32 &operationType, WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext = NULL);
        void       disableLiveSync                   ();

    protected :
    public :
                            WaveFrameworkConfigurationWorker (WaveObjectManager *pWaveObjectManager);
        virtual            ~WaveFrameworkConfigurationWorker ();
                ResourceId  savePrismConfiguration            (const string &prismConfigurationFile, const bool &syncToStandby);
                ResourceId  loadPrismConfiguration            (const string &prismConfigurationFile);
                bool        getPrismConfigurationValidity     ();
                ResourceId  changePrismConfigurationValidity  (const bool &validity );      
                WaveMessage *createMessageInstance           (const UI32 &operationCode);
                ResourceId  syncPrismConfigurationMessageHandler (FrameworkObjectManagerSyncConfigurationMessage *pFrameworkObjectManagerSyncConfigurationMessage);      

    // Now the data members

    private :
        bool        m_isPrismConfigurationValid ;
        WaveMutex  m_prismConfigurationValidityMutex;
 
    protected :
    public :
};

}

#endif // PRISMFRAMEWORKCONFIGURATIONWORKER_H
