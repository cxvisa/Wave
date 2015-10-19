/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkConfigurationWorker.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "Framework/Core/WaveFrameworkConfigurationContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManagerHaSyncWorker.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Persistence/PersistenceLocalObjectManagerLiveSyncEnableMessages.h"
#include <sys/file.h>


namespace WaveNs
{

WaveFrameworkConfigurationWorker::WaveFrameworkConfigurationWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    setWaveConfigurationValidity( true );
    if ( WAVE_MGMT_INTF_ROLE_SERVER == (FrameworkToolKit::getManagementInterfaceRole ()) )
    {
        //we dont want any waveclient to use flock mechanism to change configuration
        // only server is expected to change configuration
        createLockFileForConfigurationFile();
    }

    addOperationMap (FRAMEWORK_OBJECT_MANAGER_SYNC_CONFIGURATION_MESSAGE, reinterpret_cast<WaveMessageHandler> (&WaveFrameworkConfigurationWorker::syncWaveConfigurationMessageHandler));
}

WaveFrameworkConfigurationWorker::~WaveFrameworkConfigurationWorker ()
{
}

WaveMessage *WaveFrameworkConfigurationWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case FRAMEWORK_OBJECT_MANAGER_SYNC_CONFIGURATION_MESSAGE:
            pWaveMessage = new FrameworkObjectManagerSyncConfigurationMessage ();
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

ResourceId WaveFrameworkConfigurationWorker::saveWaveConfiguration (const string &prismConfigurationFile, const bool &syncToStandby)
{
    WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext = NULL;

    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::validateStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::initializeConfigurationStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::displayConfigurationStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::saveConfigurationStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::sendConfigurationToStandbyStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::prismSynchronousLinearSequencerFailedStep)
    };

    pWaveFrameworkConfigurationContext = new WaveFrameworkConfigurationContext (NULL, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]), prismConfigurationFile);

    pWaveFrameworkConfigurationContext->setSyncToStandby (syncToStandby);

    ResourceId status = pWaveFrameworkConfigurationContext->execute ();

    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::validateStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{
    if ( true ==  FrameworkToolKit::isNodeZeroized ()) 
    {
        trace (TRACE_LEVEL_ERROR,"WaveFrameworkConfigurationWorker::validateStep: Failed to save cfg file as node is zeroized.");

        return (WAVE_MESSAGE_ERROR);
    }
    
    if ( false == getWaveConfigurationValidity() )
    {

        if (true == pWaveFrameworkConfigurationContext->getSyncToStandby ())
        {
            trace (TRACE_LEVEL_INFO,"WaveFrameworkConfigurationWorker::validateStep: CFG file is invalid and will not save the configuration, but still sync over in-memory CFG content to standby" );
        }
        else
        {
            trace (TRACE_LEVEL_INFO,"WaveFrameworkConfigurationWorker::validateStep: CFG file is invalid and will not save the configuration" );
            return (WAVE_MESSAGE_ERROR);
        }

    }
    return (WAVE_MESSAGE_SUCCESS) ;
}

ResourceId WaveFrameworkConfigurationWorker::initializeConfigurationStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{
    WaveFrameworkConfiguration &waveFrameworkConfigurationObject = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();

    return (waveFrameworkConfigurationObject.initializeConfiguration ());
}

ResourceId WaveFrameworkConfigurationWorker::saveConfigurationStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (true == getWaveConfigurationValidity())
    {
        status = configurationWithFlock (SAVE_CONFIGURATION, pWaveFrameworkConfigurationContext);
    }
    
    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::sendConfigurationToStandbyStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;
   
    if (pWaveFrameworkConfigurationContext->getSyncToStandby () == true) 
    {

        if (FrameworkToolKit::getIsLiveSyncEnabled () == false)
        {
            if (FrameworkToolKit::getSyncState () == IN_SYNC)
            {
                // DB previously in sync from sync dump. but live transaction sync not supported. So set out of sync and notify on sync update fail
                trace (TRACE_LEVEL_WARN, "WaveFrameworkConfigurationWorker::sendConfigurationToStandbyStep: Live sync disabled. Notify sync update failure on first update after sync dump.");
                FrameworkToolKit::notifySyncUpdateFailure(WAVE_MESSAGE_ERROR_CLUSTER_STATUS_HASYNC_NOT_SUPPORTED);
            }
            return (WAVE_MESSAGE_SUCCESS);
        }

        trace (TRACE_LEVEL_INFO, "WaveFrameworkConfigurationWorker::sendConfigurationToStandbyStep : Syncing configuration to standby");

        FrameworkObjectManagerSyncConfigurationMessage *pFrameworkObjectManagerSyncConfigurationMessage = new FrameworkObjectManagerSyncConfigurationMessage ();

        pFrameworkObjectManagerSyncConfigurationMessage->setWaveFrameworkConfigurationFileName (WaveFrameworkObjectManager::getConfigurationFileName ());
       
        bool cfgValidity = getWaveConfigurationValidity(); 

        WaveFrameworkConfiguration &waveFrameworkConfigurationObject = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();

        string serializedConfigurationObject;

        waveFrameworkConfigurationObject.serialize2 (serializedConfigurationObject);

        pFrameworkObjectManagerSyncConfigurationMessage->addBuffer (CFG_OBJECT, serializedConfigurationObject.size (), (void *) (serializedConfigurationObject.c_str()), false);

        pFrameworkObjectManagerSyncConfigurationMessage->addBuffer (CFG_VALIDITY, sizeof (bool), (void *) &cfgValidity, false);

        status  = sendSynchronously (pFrameworkObjectManagerSyncConfigurationMessage, FrameworkToolKit::getHaPeerLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveFrameworkConfigurationWorker::sendConfigurationToStandbyStep : Could not send message to sync configuration.  Status : " + FrameworkToolKit::localize (status));
            FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_STATUS_HASYNC_FAILED);
        }
        else
        {
             status = pFrameworkObjectManagerSyncConfigurationMessage->getCompletionStatus ();
     
             if (WAVE_MESSAGE_SUCCESS != status)
             {
                 trace (TRACE_LEVEL_FATAL, "WaveFrameworkConfigurationWorker::sendConfigurationToStandbyStep : Message to sync configuration failed.  Completion Status : " + FrameworkToolKit::localize (status));
                 FrameworkToolKit::notifySyncUpdateFailAndStopSync(WAVE_MESSAGE_ERROR_CLUSTER_STATUS_HASYNC_FAILED); 
             }
             else
             {
                 trace (TRACE_LEVEL_INFO, "WaveFrameworkConfigurationWorker::sendConfigurationToStandbyStep: FrameworkObjectManagerSyncConfigurationMessage successfully sent.");
             }
        }

        delete (pFrameworkObjectManagerSyncConfigurationMessage);
    }

    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::loadWaveConfiguration (const string &prismConfigurationFile)
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::loadConfigurationStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::displayConfigurationStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::prismSynchronousLinearSequencerFailedStep)
    };

    WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext = new WaveFrameworkConfigurationContext (NULL, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]), prismConfigurationFile);

    ResourceId status = pWaveFrameworkConfigurationContext->execute ();

    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::loadConfigurationStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{
    string                      &waveFrameworkConfigurationFileName = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationFileName ();
    WaveFrameworkConfiguration &waveFrameworkConfigurationObject   = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();
    ResourceId status = WAVE_MESSAGE_SUCCESS;
    
    if (WAVE_MGMT_INTF_ROLE_SERVER != (FrameworkToolKit::getManagementInterfaceRole ()))
    {
        // Wave client need not use flock mechanism to change configuration
        status = waveFrameworkConfigurationObject.loadConfiguration (waveFrameworkConfigurationFileName);
    }
    else
    {
        status = configurationWithFlock (LOAD_CONFIGURATION, pWaveFrameworkConfigurationContext );
    }
    
    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::displayConfigurationStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{
    WaveFrameworkConfiguration &waveFrameworkConfigurationObject   = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();

    waveFrameworkConfigurationObject.display ();

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveFrameworkConfigurationWorker::changeWaveConfigurationValidity ( const bool &validity)
{
    
    setWaveConfigurationValidity(validity);
    ResourceId status = WAVE_MESSAGE_SUCCESS;
     
    if ( validity == false )
    {
        //Since we remove Cfg file need to acquire flock
        status = configurationWithFlock (CHANGE_CONFIGURATION_VALIDITY);
    }
    else
    {
        status = saveWaveConfiguration( WaveFrameworkObjectManager::getConfigurationFileName(), false);        
        trace (TRACE_LEVEL_INFO, "WaveFrameworkConfigurationWorker::changeWaveConfigurationValidity : Configuration File is valid now ");
    }
    
    return status;
    
}

void WaveFrameworkConfigurationWorker::setWaveConfigurationValidity(const bool &validity)
{
    m_prismConfigurationValidityMutex.lock();
    
    m_isWaveConfigurationValid = validity;
    
    m_prismConfigurationValidityMutex.unlock();
}

bool WaveFrameworkConfigurationWorker::getWaveConfigurationValidity( )
{
    m_prismConfigurationValidityMutex.lock();

    bool validity = m_isWaveConfigurationValid ;

    m_prismConfigurationValidityMutex.unlock();
    
    return validity;
}

void WaveFrameworkConfigurationWorker::createLockFileForConfigurationFile()
{
    string cmdToCreateLockFile = "/bin/touch " + WaveFrameworkObjectManager::getLockFileForConfigurationFile(); 
    vector<string>  output;
    SI32 cmdStatus = 0;
    cmdStatus = FrameworkToolKit::systemCommandOutput ( cmdToCreateLockFile, output );

    if ( cmdStatus != 0 )
    {   
        if (0 < (output.size ()))
        {
            trace (TRACE_LEVEL_ERROR, string("WaveFrameworkConfigurationWorker::createLockFileForConfigurationFile : cmdToCreateLockFile = ")+ cmdToCreateLockFile + " failed with error message : " + output[0]);
        }
        else
        {
            trace (TRACE_LEVEL_ERROR, string("WaveFrameworkConfigurationWorker::createLockFileForConfigurationFile : cmdToCreateLockFile = ")+ cmdToCreateLockFile + " failed.");
        }
    }
}

ResourceId WaveFrameworkConfigurationWorker::configurationWithFlock ( const UI32 &operationType, WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{   

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    FILE *pFile ;
    string lockFilename = WaveFrameworkObjectManager::getLockFileForConfigurationFile();
    SI32 cmdStatus = 0;

    //Acquire flock for all operation types
    pFile = fopen (lockFilename.c_str(),"w");
    
    if (pFile == NULL)
    {   
        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkConfigurationWorker::configurationWithFlock : Unable to open the lockfile --> ") + lockFilename.c_str() );
        return (WAVE_MESSAGE_ERROR);
    }
    
    if (0 != flock( fileno(pFile), LOCK_EX ))
    {   
        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkConfigurationWorker::configurationWithFlock : Unable to secure the lock on Configurationlockfile --> ") + lockFilename.c_str() );  
        fclose( pFile );
        return (WAVE_MESSAGE_ERROR);
    }

    trace (TRACE_LEVEL_DEBUG, string("WaveFrameworkConfigurationWorker::configurationWithFlock : Acquired lock on Configurationlockfile --> ") + lockFilename.c_str() );

    switch ( operationType )
    {
     
        case CHANGE_CONFIGURATION_VALIDITY :
                                    {      //This is used to invalidate the configuration                              
                                        string          cmdToDeleteCFG  = "/bin/rm -rf " + WaveFrameworkObjectManager::getConfigurationFileName();
                                        vector<string>  output;

                                        cmdStatus = FrameworkToolKit::systemCommandOutput (cmdToDeleteCFG, output);
                                        if ( cmdStatus != 0 )
                                        {   
                                            trace (TRACE_LEVEL_ERROR, string("WaveFrameworkConfigurationWorker::configurationWithFlock : cmdToDeleteCFG = ")+ cmdToDeleteCFG + " failed with error message : " + output[0]);
                                            status = WAVE_MESSAGE_ERROR;
                                        }
                                        break;
                                    }

        case SAVE_CONFIGURATION :       
                                    {
                                        if ( pWaveFrameworkConfigurationContext == NULL  )
                                        {
                                            trace (TRACE_LEVEL_ERROR,"WaveFrameworkConfigurationWorker::configurationWithFlock : pWaveFrameworkConfigurationContext for Save is Null");
                                            status = WAVE_MESSAGE_ERROR;
                                            break ;                    
                                        }                        
                                        string   &waveFrameworkConfigurationFileName = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationFileName ();
                                        WaveFrameworkConfiguration &waveFrameworkConfigurationObject   = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();                                               
                                        status = waveFrameworkConfigurationObject.saveConfiguration (waveFrameworkConfigurationFileName);
                                        break;
                                    }

        case LOAD_CONFIGURATION :
                                    {
                                        if ( pWaveFrameworkConfigurationContext == NULL  )
                                        {
                                            trace (TRACE_LEVEL_ERROR,"WaveFrameworkConfigurationWorker::configurationWithFlock : pWaveFrameworkConfigurationContext for Load is Null");
                                            status = WAVE_MESSAGE_ERROR;
                                            break ;
                                        }
                                        string   &waveFrameworkConfigurationFileName = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationFileName ();
                                        WaveFrameworkConfiguration &waveFrameworkConfigurationObject   = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();      
                                        status = waveFrameworkConfigurationObject.loadConfiguration (waveFrameworkConfigurationFileName);
                                        break;
                                    }
        default :
                                        trace (TRACE_LEVEL_ERROR, string("WaveFrameworkConfigurationWorker::configurationWithFlock : Unknown operation type = ") + operationType );
                                        status = WAVE_MESSAGE_ERROR;
                                        break;                                                         
                            
    }
    // Since the operation is complete release the flock
    flock( fileno(pFile), LOCK_UN );
    trace (TRACE_LEVEL_DEBUG, string("WaveFrameworkConfigurationWorker::configurationWithFlock : released lock on Configurationlockfile --> ") + lockFilename.c_str() );
    fclose( pFile );
    
    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::syncWaveConfigurationMessageHandler (FrameworkObjectManagerSyncConfigurationMessage *pFrameworkObjectManagerSyncConfigurationMessage)
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::resetStartupFileStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::displayConfigurationStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::setInMemoryConfiguration),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::updateWaveConfigurationFileStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveFrameworkConfigurationWorker::prismSynchronousLinearSequencerFailedStep)
    };

    string prismConfigurationFile = pFrameworkObjectManagerSyncConfigurationMessage->getWaveFrameworkConfigurationFileName ();

    WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext = new WaveFrameworkConfigurationContext (pFrameworkObjectManagerSyncConfigurationMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]), prismConfigurationFile);

    // set cfg object in context

    WaveFrameworkConfiguration &waveFrameworkConfigurationObject = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();

    UI32 sizeOfBuffer = 0;

    char *serialzedConfigurationObject = reinterpret_cast<char *> (pFrameworkObjectManagerSyncConfigurationMessage->findBuffer (CFG_OBJECT, sizeOfBuffer));

    string serializedData (serialzedConfigurationObject);

    waveFrameworkConfigurationObject.loadFromSerializedData2 (serializedData);

    ResourceId status = pWaveFrameworkConfigurationContext->execute ();

    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::updateWaveConfigurationFileStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{

    ResourceId  status              = WAVE_MESSAGE_SUCCESS;
    UI32        sizeOfBuffer        = 0;
    bool        cfgValidity         = false;

    FrameworkObjectManagerSyncConfigurationMessage *pMessage = reinterpret_cast<FrameworkObjectManagerSyncConfigurationMessage *> (pWaveFrameworkConfigurationContext->getPWaveMessage ());
    
    bool *cfgValidityPtr = reinterpret_cast<bool *> (pMessage->findBuffer (CFG_VALIDITY, sizeOfBuffer));

    if (NULL == cfgValidityPtr)
    {
        // Normally we shouldn't come here because in live sync, both MMs should have same firmware version.
        // To be safe, reset cfg validity.

        cfgValidity = true;
    }
    else
    {
        cfgValidity = (*cfgValidityPtr);
    }

    if (false == cfgValidity)
    {
        trace (TRACE_LEVEL_INFO, "WaveFrameworkConfigurationWorker::updateWaveConfigurationFileStep: remove prism configuration file.");
        status = FrameworkToolKit::changeWaveConfigurationValidity (false);
    }
    else
    {      
        trace (TRACE_LEVEL_INFO, "WaveFrameworkConfigurationWorker::updateWaveConfigurationFileStep: save prism configuration file.");
        status = FrameworkToolKit::changeWaveConfigurationValidity (true);
    }
    
    return (status);
} 

ResourceId WaveFrameworkConfigurationWorker::resetStartupFileStep (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;
    
    WaveFrameworkConfiguration &waveFrameworkConfigurationObject = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();

    waveFrameworkConfigurationObject.setIsStartupValid (FrameworkToolKit::getIsStartupValid ());
    waveFrameworkConfigurationObject.setStartupFileName (FrameworkToolKit::getStartupFileName ());
    waveFrameworkConfigurationObject.setStartupFileType (FrameworkToolKit::getStartupFileType ());

    return (status);
}

ResourceId WaveFrameworkConfigurationWorker::setInMemoryConfiguration (WaveFrameworkConfigurationContext *pWaveFrameworkConfigurationContext)
{
    ResourceId status = WAVE_MESSAGE_ERROR;

    WaveFrameworkConfiguration &waveFrameworkConfiguration = pWaveFrameworkConfigurationContext->getWaveFrameworkConfigurationObject ();

    LocationBase *pThisLocation = (WaveFrameworkObjectManager::getInstance ())->getThisLocation ();

    waveAssert (NULL != pThisLocation, __FILE__, __LINE__);

    WaveFrameworkObjectManager::updateIpAddressForThisLocation (waveFrameworkConfiguration.getThisLocationIpAddress ());

    FrameworkToolKit::setLastUsedLocationId (waveFrameworkConfiguration.getLastUsedLocationId ());

    pThisLocation->setLocationRole             (static_cast<LocationRole> (waveFrameworkConfiguration.getThisLocationRole ()));
    pThisLocation->setLocationId               (waveFrameworkConfiguration.getThisLocationLocationId ());
    pThisLocation->setClusterPrimaryLocationId (waveFrameworkConfiguration.getClusterPrimaryLocationId ());
    pThisLocation->setClusterPrimaryPort       (waveFrameworkConfiguration.getClusterPrimaryPort ());

    UI32 numberOfKnownLocations = waveFrameworkConfiguration.getKnownLocationIpAddresses ().size ();
    UI32 i                      = 0;

    pThisLocation->removeAllKnownLocations ();

    for (i = 0; i < numberOfKnownLocations; i++)
    {
        if (pThisLocation->isAKnownLocation ((waveFrameworkConfiguration.getKnownLocationLocationIds ())[i]) != true)
        {
            pThisLocation->addKnownLocation ((waveFrameworkConfiguration.getKnownLocationLocationIds ())[i], (waveFrameworkConfiguration.getKnownLocationIpAddresses ())[i], (waveFrameworkConfiguration.getKnownLocationPorts ())[i]);
        }
    }

    UI32 numberOfKnownSubLocations = waveFrameworkConfiguration.getKnownSubLocationIpAddress ().size ();

    for (i = 0; i < numberOfKnownSubLocations; i++)
    {
        pThisLocation->addSubLocation ((waveFrameworkConfiguration.getKnownSubLocationLocationIds ())[i], (waveFrameworkConfiguration.getKnownSubLocationIpAddress ())[i], (waveFrameworkConfiguration.getKnownSubLocationPorts ())[i]);
    }

    status = WAVE_MESSAGE_SUCCESS;

    return (status);
}

}
