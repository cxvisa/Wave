/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Framework/Core/Wave.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "App/AppObjectManager.h"
#include "App/AppInterfaceObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include <map>
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"

namespace WaveNs
{

static map<WaveServiceId, WaveServiceId> s_applicationSpecificServicesMap;
static WaveMutex                          s_applicationSpecificServicesMutex;

// Vector for application registered to start with Wave.
// Application will register using registerApp which should be called before
// calling WaveMain.

static vector <AppDetail *>               s_appsInfo;

void AppObjectManager::addToApplicationSpecificServicesVector (const WaveServiceId &waveServiceId)
{
    s_applicationSpecificServicesMutex.lock ();
    s_applicationSpecificServicesMap[waveServiceId] = waveServiceId;
    s_applicationSpecificServicesMutex.unlock ();
}

bool AppObjectManager::isAnApplicationSpecificService (const WaveServiceId &waveServiceId)
{
    bool serviceFound = false;

    s_applicationSpecificServicesMutex.lock ();

    map<WaveServiceId, WaveServiceId>::iterator element = s_applicationSpecificServicesMap.find (waveServiceId);
    map<WaveServiceId, WaveServiceId>::iterator end     = s_applicationSpecificServicesMap.end ();

    if (element != end)
    {
        serviceFound = true;
    }
    else
    {
        serviceFound = false;
    }

    s_applicationSpecificServicesMutex.unlock ();

    return (serviceFound);
}

    // NOTE: This class is not a singleton. We will cerate an instance of
    // this class for each application registered with Wave. The application
    // will be running on this objectManager thread.
AppObjectManager::AppObjectManager (AppDetail *appDetail, UI32 applicationId, const UI32 &stackSize)
    : WaveLocalObjectManagerForUserSpecificTasks (appDetail->getAppName (), stackSize)
{
    addToApplicationSpecificServicesVector (getServiceId ());

    m_applicationMain = appDetail->getApplicationMain ();
    m_argc            = appDetail->getArgc ();
    m_argv            = appDetail->getArgv ();
    m_applicationId   = applicationId;
}

    // Again, this is not a singleton. Each time we call createInstance we will get
    // a different ObjectManager.

AppObjectManager *AppObjectManager::createInstance (AppDetail *appDetail, UI32 applicationId)
{
    static UI32 s_applicationStackSize = 2 * 1024 * 1024; // for Applications by default we use 2 MB of stack.

    WaveNs::trace (TRACE_LEVEL_DEBUG, "AppObjectManager::createInstance : Entering ...");

    AppObjectManager *pAppObjectManager = new AppObjectManager (appDetail, applicationId, s_applicationStackSize);

    WaveNs::waveAssert (NULL != pAppObjectManager, __FILE__, __LINE__);
    return (pAppObjectManager);

}


AppObjectManager::~AppObjectManager ()
{
}

void AppObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    WaveNs::trace (TRACE_LEVEL_DEBUG, "AppObjectManager::boot : Entering ...") ;

    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();


    if (m_applicationMain != NULL)
    {
        m_applicationMain (m_argc, m_argv, m_applicationId);
    }
}

    // Register application with Wave. Wave will create objectManager for this
    // application and running the application in that thread.
    // No limit for number of application that can register with Wave.
    // Two version are provided for this function. with argumentw and without.

SI32 AppObjectManager::registerApp (string appName, applicationMainFunction applicationMain)
{
    UI32        i;

    cout << "AppObjectManager::registerApp : Entering ..." << endl;

    for (i = 0; i < s_appsInfo.size (); i++)
    {
        if (s_appsInfo[i]->getAppName () == appName)
        {
            return (i);
        }
    }

    AppDetail   *appDetail = new AppDetail (appName, applicationMain);
    s_appsInfo.push_back (appDetail);
    return (s_appsInfo.size () -1);
}

SI32 AppObjectManager::registerApp (string appName, applicationMainFunction applicationMain, UI32 argc, char *argv[])
{
    UI32        i;

    cout << "AppObjectManager::registerApp : Entering ..." << endl;

    for (i = 0; i < s_appsInfo.size (); i++)
    {
        if (s_appsInfo[i]->getAppName () == appName)
        {
            return (i);
        }
    }

    AppDetail   *appDetail = new AppDetail (appName, applicationMain, argc, argv);
    s_appsInfo.push_back (appDetail);
    return (s_appsInfo.size () -1);
}


bool AppObjectManager::validateAppId (SI32 appId)
{
    if (appId == -1)
    {
        return (true);
    }

    if (appId < -1)
    {
        return (false);
    }

    if((UI32) appId >= s_appsInfo.size ())
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

AppInterfaceObjectManager *AppObjectManager::getAppInterfaceObjectManagerForServiceId (UI32 appInterafceServiceId)
{
    UI32    appId;

    for (appId = 0; appId < s_appsInfo.size (); appId++)
    {
        if (s_appsInfo[appId]->getAppInterfaceServiceId () == appInterafceServiceId)
        {
            return (s_appsInfo[appId]->getAppInterfaceObjectManager ());
        }
    }
    return (NULL);
}

AppInterfaceObjectManager *AppObjectManager::getAppInterfaceObjectManager (UI32 appId)
{
    return (s_appsInfo[appId]->getAppInterfaceObjectManager ());
}

AppObjectManager *AppObjectManager::getAppObjectManager (UI32 appId)
{
    return (s_appsInfo[appId]->getAppObjectManager ());
}

    // This is called after creating Wave object managers. This function will create the
    // object managers for all the application registered with wave.

void AppObjectManager::createAppObjectMangers ()
{
    UI32                      i;
    AppObjectManager          *appObjectManager;
    AppInterfaceObjectManager *appInterfaceObjectManager;
    AppDetail                 *appDetail;
    string                     appInterfaceName;

    WaveNs::trace (TRACE_LEVEL_DEBUG, "AppObjectManager::createAppObjectMangers : Entering ...");

    for (i = 0; i < s_appsInfo.size (); i++)
    {
        // create application object manager.
        appDetail = s_appsInfo[i];
        appInterfaceName    =   appDetail->getAppName () + " Interface";

        appObjectManager            = AppObjectManager::createInstance (appDetail, i);
        appInterfaceObjectManager   = AppInterfaceObjectManager::createInstance (appInterfaceName);
        appDetail->setAppObjectManager (appObjectManager);
        appDetail->setAppInterfaceObjectManager (appInterfaceObjectManager);
        appDetail->setAppInterfaceServiceId (appInterfaceObjectManager->getWaveServiceId ());
        appDetail->setAppServiceId (appObjectManager->getServiceId ());
        // Add the created object manager to wave init/boot/... steps
        FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
        frameworkSequenceGenerator.addWaveServiceIdToAll        (appObjectManager->getServiceId ());
        frameworkSequenceGenerator.addWaveServiceIdToAll        (appInterfaceObjectManager->getWaveServiceId ());
    }
}




AppDetail::AppDetail ()
{
    m_applicationMain           = NULL;
    m_argc                      = 0;
    m_argv                      = NULL;
    m_appInterfaceObjectManager = NULL;
    m_appObjectManager          = NULL;
    m_appInterfaceServiceId     = 0;
    m_appServiceId              = 0;

}

AppDetail::AppDetail (string appName, applicationMainFunction applicationMain)
{
    m_appName         = appName;
    m_applicationMain = applicationMain;
    m_argc            = 0;
    m_argv            = NULL;
    m_appInterfaceObjectManager = NULL;
    m_appObjectManager          = NULL;
    m_appInterfaceServiceId     = 0;
    m_appServiceId              = 0;

}

AppDetail::AppDetail (string appName, applicationMainFunction applicationMain, UI32 argc, char *argv[])
{
    m_appName         = appName;
    m_applicationMain = applicationMain;
    m_argc            = argc;
    m_argv            = argv;
    m_appInterfaceObjectManager = NULL;
    m_appObjectManager          = NULL;
    m_appInterfaceServiceId     = 0;
    m_appServiceId              = 0; 
}

AppDetail::~AppDetail ()
{
}

void AppDetail::setAppName (string appName)
{
    m_appName = appName;
}

string AppDetail::getAppName ()
{
    return (m_appName);
}

void AppDetail::setApplicationMain (applicationMainFunction applicationMain)
{
    m_applicationMain = applicationMain;
}

applicationMainFunction AppDetail::getApplicationMain ()
{
    return (m_applicationMain);
}

void AppDetail::setAppObjectManager (AppObjectManager *appObjectManager)
{
    m_appObjectManager = appObjectManager;
}

AppObjectManager * AppDetail::getAppObjectManager ()
{
    return (m_appObjectManager);
}


void AppDetail::setAppInterfaceObjectManager (AppInterfaceObjectManager *appInterfaceObjectManager)
{
    m_appInterfaceObjectManager = appInterfaceObjectManager;
}

AppInterfaceObjectManager * AppDetail::getAppInterfaceObjectManager ()
{
    return (m_appInterfaceObjectManager);
}

void AppDetail::setArgc (UI32 argc)
{
    m_argc = argc;
}

UI32 AppDetail::getArgc ()
{
    return (m_argc);
}

void AppDetail::setArgv (char *argv[])
{
    m_argv  =   argv;
}

char **AppDetail::getArgv ()
{
    return (m_argv);
}

void AppDetail::setAppInterfaceServiceId (UI32 appInterfaceServiceId)
{
    m_appInterfaceServiceId = appInterfaceServiceId;
}

void AppDetail::setAppServiceId (UI32 appServiceId)
{
    m_appServiceId = appServiceId;
}


UI32 AppDetail::getAppInterfaceServiceId ()
{
    return (m_appInterfaceServiceId);
}

UI32 AppDetail::getAppServiceId ()
{
    return (m_appServiceId);
}
}
