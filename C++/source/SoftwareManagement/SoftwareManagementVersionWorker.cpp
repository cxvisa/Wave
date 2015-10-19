/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SoftwareManagement/SoftwareManagementVersionWorker.h"
#include "SoftwareManagement/SoftwareManagementObjectManager.h"
#include "SoftwareManagement/SoftwareManagementTypes.h"
#include "SoftwareManagement/SoftwareManagementGetVersionMessage.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Version/WaveVersion.h"
#include "Shell/ShellDebug.h"
#include "ManagementInterface/ClientInterface/WaveClientSynchronousConnection.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

SoftwareManagementVersionWorker::SoftwareManagementVersionWorker (SoftwareManagementObjectManager *pSoftwareManagementObjectManager)
    : WaveWorker (pSoftwareManagementObjectManager)
{
    addDebugFunction ((ShellCmdFunction) (&SoftwareManagementVersionWorker::debugGetVersion), "getversion");

    addOperationMap (SOFTWAREMANAGEMENT_GET_VERSION, reinterpret_cast<WaveMessageHandler> (&SoftwareManagementVersionWorker::softwareManagementGetVersionMessageHandler));
}

SoftwareManagementVersionWorker::~SoftwareManagementVersionWorker ()
{
}

WaveMessage *SoftwareManagementVersionWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case SOFTWAREMANAGEMENT_GET_VERSION :
            pWaveMessage = new SoftwareManagementGetVersionMessage;
            break;

        default :
            pWaveMessage = NULL;
    }

    return (pWaveMessage);
}

void SoftwareManagementVersionWorker::softwareManagementGetVersionMessageHandler (SoftwareManagementGetVersionMessage *pSoftwareManagementGetVersionMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&SoftwareManagementVersionWorker::getVersionStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SoftwareManagementVersionWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&SoftwareManagementVersionWorker::waveLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pSoftwareManagementGetVersionMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->start ();
}

void SoftwareManagementVersionWorker::getVersionStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "SoftwareManagementVersionWorker::getVersionStep : Entering ...");

          SoftwareManagementGetVersionMessage *pSoftwareManagementGetVersionMessage = reinterpret_cast<SoftwareManagementGetVersionMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());
    const WaveVersion                        *pWaveVersion                        = WaveVersion::getInstance ();
    const string                               version                              = pWaveVersion->getMajor () + "." + pWaveVersion->getMinor () + "." + pWaveVersion->getPatch () + "." + pWaveVersion->getRevision () + "-" + pWaveVersion->getBuildType () + "." + pWaveVersion->getBuildNumber ();

    pSoftwareManagementGetVersionMessage->setVersion (version);

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void SoftwareManagementVersionWorker::debugGetVersion (UI32 argc, vector<string> argv)
{
    string serverIpAddress              = FrameworkToolKit::getAPublicIpAddressForThisMachine ();
    UI32   serverPort                   = 9111;
    char   serverIpCharArray[64] = {0};
    UI32   i;

    for (i = 0; i < argc; i += 1)
    {
        if (0 == strcasecmp ("-serverip", argv[i].c_str ()))
        {
            if (argc > (i + 1))
            {
                strncpy (serverIpCharArray, argv[i + 1].c_str (), 63);
                serverIpAddress = serverIpCharArray;
                i++;
            }
        }
        else if (0 == strcasecmp ("-serverport", argv[i].c_str ()))
        {
            if (argc > (i + 1))
            {
                serverPort = atoi (argv[i + 1].c_str ());
                i++;
            }
        }
    }

    WaveNs::trace (TRACE_LEVEL_DEBUG, "SoftwareManagementVersionWorker::debugGetVersion : Server IP Address : " + serverIpAddress + string (", Port : ") + serverPort);

    WaveClientSynchronousConnection connection ("Wave Debug Client", serverIpAddress, serverPort);

    WaveConnectionStatus connectionstatus = WAVE_MGMT_CLIENT_INTF_CONNECTION_ESTABLISHED_TO_SERVER;
    string               version;

    connectionstatus = connection.connect ();

    if (WAVE_MGMT_CLIENT_INTF_CONNECTION_ESTABLISHED_TO_SERVER == connectionstatus)
    {
        ResourceId status = connection.getVersion (version);

        if (WAVE_MESSAGE_SUCCESS == status)
        {
            WaveNs::trace (TRACE_LEVEL_INFO, string ("SoftwareManagementVersionWorker::debugGetVersion : IP Address : \"") + serverIpAddress + string ("\""));
            WaveNs::trace (TRACE_LEVEL_INFO, string ("SoftwareManagementVersionWorker::debugGetVersion : Port       : \"") + serverPort + string ("\""));
            WaveNs::trace (TRACE_LEVEL_INFO, string ("SoftwareManagementVersionWorker::debugGetVersion : Version    : \"") + version + string ("\""));
        }
        else
        {
            WaveNs::trace (TRACE_LEVEL_ERROR, "SoftwareManagementVersionWorker::debugGetVersion : Failed to obtain version from the server.  Status : " + FrameworkToolKit::localize (status));
        }
    }
    else
    {
        WaveNs::trace (TRACE_LEVEL_ERROR, "Could not establish connection to Wave Server");
    }

    connection.close ();
}

}
