/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveClient.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/WaveSourceGenerator/WaveSourceGeneratorBase.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Trace/TraceObjectManager.h"
#include "App/AppInterfaceObjectManager.h"
#include "App/AppObjectManager.h"
#include "Shell/ShellObjectManager.h"
#include "Framework/Timer/TimerObjectManager.h"
#include "Framework/Timer/TimerSignalObjectManager.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/ServiceInterface/ApplicationService.h"
#include "Framework/ServiceInterface/ApplicationLocalService.h"
#include "ManagementInterface/ClientInterface/WaveClientReceiverObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveClientTransportObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"
#include "Framework/Profiling/WaveProfiler.h"

#include <time.h>
#include <stdlib.h>

#include "Sharding/ShardingCapabilitiesToolKit.h"

//Commenting it our for now.  We need to find way to enable it on Solaris.
//extern int daemon (int doNotChangeToRootDir, int doNotCloseFileDescriptors);

static string s_waveClientTraceFileDirectory         ("");
static string s_waveClientConfigurationFileDirectory ("");
static string s_waveClientProfileFileDirectory       ("");

namespace WaveNs
{

vector<NativeWaveServiceInstantiator>         WaveClient::m_nativeWaveServiceInstantiators;
vector<bool>                                   WaveClient::m_nativeWaveServiceInstantiatorIsForNormalPhase;
vector<NativeMultipleWaveServiceInstantiator> WaveClient::m_nativeMultipleWaveServiceInstantiators;
UpdateClientStatusFunctionPtr                  WaveClient::m_updateClientStatusFunctionPtr = NULL;
WaveMutex                                     WaveClient::m_updateClientStatusFunctionPtrMutex;

void WaveClient::initialize (const WaveClientConfiguration &waveClientConfiguration)
{
    // Initialize Random Generator

    srand (time (NULL));

    // Set the Management Interface Role

    FrameworkToolKit::setManagementInterfaceRole (WAVE_MGMT_INTF_ROLE_CLIENT);

    // Set if the database is to be enabled.

    DatabaseObjectManager::setIsDatabaseEnabled (waveClientConfiguration.getIsDatabaseEnabled());
    DatabaseObjectManager::setDatabasePort (waveClientConfiguration.getDatabasePort());

    // First record the current working directory as the directory in which the process was started

    FrameworkToolKit::initialize ();

    ShardingCapabilitiesToolKit::initialize ();

    // set the WaveClient Framework configuration file.

    WaveFrameworkObjectManager::setConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveClientConfiguration.getApplicationCompactName() + ".cfg");
    WaveFrameworkObjectManager::setGlobalConfigurationFile ((getConfigurationFileDirectory ()) + "/" + waveClientConfiguration.getApplicationCompactName() + ".global.cfg");

    // Set the trace file name first

    TraceObjectManager::setTraceFileName ((getTraceFileDirectory ()) + "/" + waveClientConfiguration.getApplicationCompactName() + ".trc");

    // Set the profile file namespace

    WaveProfiler::setProfileFileName ((getProfileFileDirectory ()) + "/" + waveClientConfiguration.getApplicationCompactName() + ".wpd");

    // Set if logging to syslog is required

    TraceObjectManager::setIsSysLogRequired (waveClientConfiguration.getIsSysLogRequired ());

    // Record if the process is running as a daemon.

    FrameworkToolKit::setIsRunningAsADaemon (false);

    // WaveFrameworkObjectManager must be the first one to be created.

    WaveFrameworkObjectManager::getInstance ();

    // WARNING! WARNING! WARNING!
    // DO NOT CHANGE ABOVE THIS LINE

    // Below this one the services are registered in reverse order.  The last one will be on top of the list.

    if (true == waveClientConfiguration.getNeedShell ())
    {
        registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (ShellObjectManager::getInstance));

        FrameworkToolKit::registerDebugShellEntries ();
        WaveSourceGeneratorBase::registerDebugShellEntries ();
        WaveClientReceiverObjectManager::registerDebugShellEntries ();
    }

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveUserInterfaceObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveClientTransportObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (WaveClientReceiverObjectManager::getInstance));

    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerObjectManager::getInstance));
    registerNativeServiceInternal (reinterpret_cast<NativeWaveServiceInstantiator> (TimerSignalObjectManager::getInstance));

    // Instantiate Native WaveClient Services here

    instantiateNativeWaveServices ();

    // Start the ObjectManager s corresponding to Application Services

    ApplicationService::createNewApplicationServices ();

    // start the ObjectManager s corresponding to Application Local Services

    ApplicationLocalService::createNewApplicationLocalServices ();

    // Starting Application specfic Object managers.

    AppObjectManager::createAppObjectMangers ();
}

string WaveClient::getTraceFileDirectory ()
{
    static WaveMutex traceFileDirectoryMutex;

    traceFileDirectoryMutex.lock ();

    if ("" != s_waveClientTraceFileDirectory)
    {
        traceFileDirectoryMutex.unlock ();
        return (s_waveClientTraceFileDirectory);
    }
    else
    {
        s_waveClientTraceFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveClientTraceFileDirectory)
        {
            s_waveClientTraceFileDirectory = "/tmp";
        }
    }

    traceFileDirectoryMutex.unlock ();

    return (s_waveClientTraceFileDirectory);
}

string WaveClient::getConfigurationFileDirectory ()
{
    static WaveMutex configurationFileDirectoryMutex;

    configurationFileDirectoryMutex.lock ();

    if ("" != s_waveClientConfigurationFileDirectory)
    {

    configurationFileDirectoryMutex.unlock ();
        return (s_waveClientConfigurationFileDirectory);
    }
    else
    {
        s_waveClientConfigurationFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveClientConfigurationFileDirectory)
        {
            s_waveClientConfigurationFileDirectory = "/tmp";
        }
    }

    configurationFileDirectoryMutex.unlock ();

    return (s_waveClientConfigurationFileDirectory);
}

string WaveClient::getProfileFileDirectory ()
{
    static WaveMutex profileFileDirectoryMutex;

    profileFileDirectoryMutex.lock ();

    if ("" != s_waveClientProfileFileDirectory)
    {
        profileFileDirectoryMutex.unlock ();
        return (s_waveClientProfileFileDirectory);
    }
    else
    {
        s_waveClientProfileFileDirectory = FrameworkToolKit::getProcessInitialWorkingDirectory ();

        if ("" == s_waveClientProfileFileDirectory)
        {
            s_waveClientProfileFileDirectory = "/tmp";
        }
    }

    profileFileDirectoryMutex.unlock ();

    return (s_waveClientProfileFileDirectory);
}

//This is used to register the funcptr invoked by updateclientstatus
void WaveClient::registerUpdateClientStatusFunction ( UpdateClientStatusFunctionPtr  pUpdateClientStatusFunctionPtr  )
{
    m_updateClientStatusFunctionPtrMutex.lock();
    m_updateClientStatusFunctionPtr = pUpdateClientStatusFunctionPtr;
    m_updateClientStatusFunctionPtrMutex.unlock();
}

// This function will be called by WaveUserInterfaceOM to update status received from Server
// Inturn the client registered funcptr is invoked passing the message
SI32 WaveClient::updateClientStatusFunction( ManagementInterfaceMessage *pManagementInterfaceMessage  )
{
    SI32 status = 0;
    if ( m_updateClientStatusFunctionPtr != NULL  )
    {
        m_updateClientStatusFunctionPtrMutex.lock();
        status = m_updateClientStatusFunctionPtr ( pManagementInterfaceMessage );
        m_updateClientStatusFunctionPtrMutex.unlock();
    }
    return (status);
}

void WaveClient::registerNativeService (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase)
{
    m_nativeWaveServiceInstantiators.push_back                (pNativeWaveServiceInstantiator);
    m_nativeWaveServiceInstantiatorIsForNormalPhase.push_back (isForNormalPhase);
}

void WaveClient::registerNativeServiceInternal (NativeWaveServiceInstantiator pNativeWaveServiceInstantiator, const bool &isForNormalPhase)
{
    m_nativeWaveServiceInstantiators.insert                (m_nativeWaveServiceInstantiators.begin (), pNativeWaveServiceInstantiator);
    m_nativeWaveServiceInstantiatorIsForNormalPhase.insert (m_nativeWaveServiceInstantiatorIsForNormalPhase.begin (), isForNormalPhase);
}

void WaveClient::registerNativeService (NativeMultipleWaveServiceInstantiator pNativeMultipleWaveServiceInstantiator)
{
    m_nativeMultipleWaveServiceInstantiators.push_back (pNativeMultipleWaveServiceInstantiator);
}

void WaveClient::instantiateNativeWaveServices ()
{
    FrameworkSequenceGenerator &frameworkSequenceGenerator                       = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
    UI32                        numberOfNativeWaveServciesToInstantiate         = m_nativeWaveServiceInstantiators.size ();
    UI32                        numberOfNativeMultipleWaveServciesToInstantiate = m_nativeMultipleWaveServiceInstantiators.size ();
    UI32                        i                                                = 0;
    UI32                        j                                                = 0;
    WaveObjectManager         *pWaveObjectManager                              = NULL;

    for (i = 0; i < numberOfNativeWaveServciesToInstantiate; i++)
    {
        pWaveObjectManager = (*(m_nativeWaveServiceInstantiators[i])) ();

        waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

        frameworkSequenceGenerator.addWaveServiceIdToAll (pWaveObjectManager->getServiceId (), m_nativeWaveServiceInstantiatorIsForNormalPhase[i]);
    }

    for (i = 0; i < numberOfNativeMultipleWaveServciesToInstantiate; i++)
    {
        vector<WaveObjectManager *> objectManagers         = (*(m_nativeMultipleWaveServiceInstantiators[i])) ();
        UI32                         numberOfObjectManagers = objectManagers.size ();

        for (j = 0; j < numberOfObjectManagers; j++)
        {
            pWaveObjectManager = objectManagers[j];

            waveAssert (NULL != pWaveObjectManager, __FILE__, __LINE__);

            frameworkSequenceGenerator.addWaveServiceIdToAll (pWaveObjectManager->getServiceId ());
        }
    }

    trace (TRACE_LEVEL_DEBUG, string ("Instantiated ") + numberOfNativeWaveServciesToInstantiate + " Native WaveClient Services");
}

}

extern "C" void setWaveClientTraceFileDirectory (const char *pWaveTraceFileDirectory)
{
    s_waveClientTraceFileDirectory = pWaveTraceFileDirectory;
}

extern "C" void setWaveClientConfigurationFileDirectory (const char *pWaveConfigurationFileDirectory)
{
    s_waveClientConfigurationFileDirectory = pWaveConfigurationFileDirectory;
}
