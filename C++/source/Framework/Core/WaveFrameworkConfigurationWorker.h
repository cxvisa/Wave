/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKCONFIGURATIONWORKER_H
#define WAVEFRAMEWORKCONFIGURATIONWORKER_H

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
        ResourceId updateWaveConfigurationFileStep  (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        ResourceId setInMemoryConfiguration          (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext);
        void       setWaveConfigurationValidity     (const bool &validity);
        void       createLockFileForConfigurationFile( ); 
        ResourceId configurationWithFlock ( const UI32 &operationType, WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext = NULL);
        void       disableLiveSync                   ();

    protected :
    public :
                            WaveFrameworkConfigurationWorker (WaveObjectManager *pWaveObjectManager);
        virtual            ~WaveFrameworkConfigurationWorker ();
                ResourceId  saveWaveConfiguration            (const string &prismConfigurationFile, const bool &syncToStandby);
                ResourceId  loadWaveConfiguration            (const string &prismConfigurationFile);
                bool        getWaveConfigurationValidity     ();
                ResourceId  changeWaveConfigurationValidity  (const bool &validity );      
                WaveMessage *createMessageInstance           (const UI32 &operationCode);
                ResourceId  syncWaveConfigurationMessageHandler (FrameworkObjectManagerSyncConfigurationMessage *pFrameworkObjectManagerSyncConfigurationMessage);      

    // Now the data members

    private :
        bool        m_isWaveConfigurationValid ;
        WaveMutex  m_prismConfigurationValidityMutex;
 
    protected :
    public :
};

}

#endif // WAVEFRAMEWORKCONFIGURATIONWORKER_H
