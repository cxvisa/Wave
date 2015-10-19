/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <iostream>
#include "Framework/Core/WaveClient.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveClientConfiguration.h"

using namespace WaveNs;

namespace WaveNs
{
}

extern "C" int waveClientMain (int argc, char *argv[], bool wait)
{
    bool                  isADaemon            = true;
    FrameworkSequenceType type                 = FRAMEWORK_SEQUENCE_TYPE0;
    bool                  isSysLogRequired     = true;
    SI32                  port                 = FrameworkToolKit::getWaveDefaultTcpPort ();
    bool                  isDatabaseEnabled    = false;
    SI32                  databasePort         = FrameworkToolKit::getWaveDefaultDatabaseTcpPort ();
    SI32                  managementClientPort = FrameworkToolKit::getManagementInterfaceClientReceiverPort ();

    if (argc >= 2)
    {
        if (0 == (strcmp (argv[1], "false")))
        {
            isADaemon = false;
        }
    }

    if (argc >= 3)
    {
        if (0 == (strcmp (argv[2], "0")))
        {
            type = FRAMEWORK_SEQUENCE_TYPE0;
        }
        else if (0 == (strcmp (argv[2], "1")))
        {
            type = FRAMEWORK_SEQUENCE_TYPE1;
        }
    }

    if (argc >= 4)
    {
        if (0 == (strcmp (argv[3], "true")))
        {
            isSysLogRequired = true;
        }
        else
        {
            isSysLogRequired = false;
        }
    }

    if (argc >= 5)
    {
        port = atoi (argv[4]);
    }

    if (argc >= 6)
    {
        if (0 == (strcmp (argv[5], "true")))
        {
            isDatabaseEnabled = true;
        }
        else
        {
            isDatabaseEnabled = false;
        }
    }

    if (argc >= 7)
    {
        databasePort = atoi (argv[6]);
    }

    if (argc >= 8)
    {
        managementClientPort = atoi (argv[7]);
    }

    FrameworkToolKit::setManagementInterfaceClientReceiverPort (managementClientPort);


    initializeWaveSocketLayer ();

#if 0
    char hostName[257];

    if (0 == (gethostname (hostName, 257)))
    {
        cout << "Host Name           : " << hostName << endl;
    }
    else
    {
        cout << "Host Name           : " << "U K N O W N" << endl;
    }
#endif

    string ipAddress = FrameworkToolKit::getAPublicIpAddressForThisMachine ();

#if 0
    cout << "Host IP Address     : " << ipAddress << endl;
    cout << "     Port           : " << port << endl;
#endif

    WaveFrameworkObjectManager::setIpAddressForThisLocation (ipAddress);

    WaveFrameworkObjectManager::setFrameworkSequenceType (type);
    WaveFrameworkObjectManager::configureAsLocation (port);

    WaveClientConfiguration waveClientConfiguration;

    waveClientConfiguration.setApplicationName   (argv[0]);
    waveClientConfiguration.setIsADaemon         (isADaemon);
    waveClientConfiguration.setIsSysLogRequired  (isSysLogRequired);
    waveClientConfiguration.setIsDatabaseEnabled (isDatabaseEnabled);
    waveClientConfiguration.setDatabasePort      (databasePort);
    waveClientConfiguration.setNeedShell         (wait);

    WaveClient::initialize (waveClientConfiguration);

    WaveFrameworkObjectManager::bootWave ();

    WaveFrameworkObjectManager::acquireBootSynchronizationMutex ();
    WaveFrameworkObjectManager::releaseBootSynchronizationMutex ();

    if (true == wait)
    {
        WaveFrameworkObjectManager::waitForWaveServicesToFinish ();
    }

    return EXIT_SUCCESS;
}
