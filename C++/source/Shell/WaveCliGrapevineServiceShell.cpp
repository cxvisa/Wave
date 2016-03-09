/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Shell/WaveCliGrapevineServiceShell.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

#include <stdlib.h>

namespace WaveNs
{

WaveCliGrapevineServiceShell::WaveCliGrapevineServiceShell (WaveClientSynchronousConnection &connection)
    : WaveCliShell ("grapevine-service", connection)
{
    addCommandfunction ("configure-service-shell",                         reinterpret_cast<WaveShellCommandFunction> (&WaveCliGrapevineServiceShell::configureServiceShell),                       "Configures a grapevine service shell.",                         reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliGrapevineServiceShell::configureServiceShellHelp));

    addCommandfunction ("register-service-instance-sharding-capabilities", reinterpret_cast<WaveShellCommandFunction> (&WaveCliGrapevineServiceShell::registerServiceInstanceShardingCapabilities), "Registers a grapevine service instance sharding capabilities.", reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliGrapevineServiceShell::registerServiceInstanceShardingCapabilitiesHelp));
}

WaveCliGrapevineServiceShell::~WaveCliGrapevineServiceShell ()
{
}

void WaveCliGrapevineServiceShell::briefHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Grapevine interaction with Service Coordinator for service / service-instance management.");
}

ResourceId WaveCliGrapevineServiceShell::configureServiceShell (const vector<string> &arguments)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (0 < (arguments.size ()))
    {
        setShellName (arguments[0]);
    }

    return (status);
}

void WaveCliGrapevineServiceShell::configureServiceShellHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE : list");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Registers an external non-native application with Service Coordinator.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "INPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  name");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Unique Name of the service ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "OUTPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
}

ResourceId WaveCliGrapevineServiceShell::registerServiceInstanceShardingCapabilities (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (2 > (arguments.size ()))
    {
        registerServiceInstanceShardingCapabilitiesHelp ();

        return (status);
    }

    status = connection.registerExternalNonNativeServiceInstance (arguments[0], arguments[1]);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliGrapevineServiceShell::registerServiceInstance : Successfully registered service instance." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliGrapevineServiceShell::registerServiceInstance : Failed to register service instance. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliGrapevineServiceShell::registerServiceInstanceShardingCapabilitiesHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE : register-service-instance <service-name> <service-instance-name>");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Registers an external non-native service instance with Service Coordinator.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "INPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  service-name");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Unique Name of the service ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  service-instance-name");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Unique Name of the service instance");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "OUTPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
}

}
