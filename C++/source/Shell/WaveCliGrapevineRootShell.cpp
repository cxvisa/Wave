/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Shell/WaveCliGrapevineRootShell.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

#include <stdlib.h>

namespace WaveNs
{

WaveCliGrapevineRootShell::WaveCliGrapevineRootShell (WaveClientSynchronousConnection &connection)
    : WaveCliShell ("grapevine", connection)
{
    addCommandfunction ("register-service",           reinterpret_cast<WaveShellCommandFunction> (&WaveCliGrapevineRootShell::registerService), "Registers a grapevine service.", reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliGrapevineRootShell::registerServiceHelp));
    addCommandfunction ("register-services-by-range", reinterpret_cast<WaveShellCommandFunction> (&WaveCliGrapevineRootShell::registerServicesByRange), "Registers grapevine services using range", reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliGrapevineRootShell::registerServicesByRangeHelp));

    addCommandfunction ("register-service-instance",           reinterpret_cast<WaveShellCommandFunction> (&WaveCliGrapevineRootShell::registerServiceInstance), "Registers a grapevine service instance.", reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliGrapevineRootShell::registerServiceInstanceHelp));
    addCommandfunction ("register-service-instances-by-range", reinterpret_cast<WaveShellCommandFunction> (&WaveCliGrapevineRootShell::registerServiceInstancesByRange), "Registers grapevine service instances using range", reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliGrapevineRootShell::registerServiceInstancesByRangeHelp));
}

WaveCliGrapevineRootShell::~WaveCliGrapevineRootShell ()
{
}

void WaveCliGrapevineRootShell::briefHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Grapevine interaction with Service Coordinator for service / service-instance management.");
}

ResourceId WaveCliGrapevineRootShell::registerService (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (1 > (arguments.size ()))
    {
        registerServiceHelp ();

        return (status);
    }

    status = connection.registerExternalNonNativeService (arguments[0]);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliGrapevineRootShell::showRunningConfiguration : Successfully registered services." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "Failed to Obtain the Managed Objects. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliGrapevineRootShell::registerServiceHelp ()
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

ResourceId WaveCliGrapevineRootShell::registerServicesByRange (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (2 > (arguments.size ()))
    {
        registerServiceHelp ();

        return (status);
    }

    const string       applicationNamePrefix = arguments[0];
    const string       applicationRange      = arguments[1];
    const UI32Range    range                   (applicationRange);
          UI32         i                     = 0;

          vector<UI32> rangeVector;

    range.getUI32RangeVector (rangeVector);

    const UI32      numberofValuesInRange    = rangeVector.size ();

    vector<string> generatedApplicationNames;

    for (i = 0; i < numberofValuesInRange; i++)
    {
        generatedApplicationNames.push_back (applicationNamePrefix + rangeVector[i]);
    }

    status = connection.registerExternalNonNativeServices (generatedApplicationNames);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliGrapevineRootShell::showRunningConfiguration : Successfully registered services." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "Failed to Obtain the Managed Objects. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliGrapevineRootShell::registerServicesByRangeHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE : list");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Registers an external non-native application with Service Coordinator.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "INPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  name");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Unique Name prefix of the service ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  range");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    comma separated range to generate service name after combining with prefix.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "OUTPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
}

ResourceId WaveCliGrapevineRootShell::registerServiceInstance (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (2 > (arguments.size ()))
    {
        registerServiceHelp ();

        return (status);
    }

    status = connection.registerExternalNonNativeServiceInstance (arguments[0], arguments[1]);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliGrapevineRootShell::registerServiceInstance : Successfully registered service instance." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliGrapevineRootShell::registerServiceInstance : Failed to register service instance. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliGrapevineRootShell::registerServiceInstanceHelp ()
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

ResourceId WaveCliGrapevineRootShell::registerServiceInstancesByRange (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (3 > (arguments.size ()))
    {
        registerServiceHelp ();

        return (status);
    }

    const string       applicationName               = arguments[0];
    const string       applicationInstanceNamePrefix = arguments[1];
    const string       applicationInstanceRange      = arguments[2];
    const UI32Range    range                           (applicationInstanceRange);
          UI32         i                             = 0;

          vector<UI32> rangeVector;

    range.getUI32RangeVector (rangeVector);

    const UI32      numberofValuesInRange    = rangeVector.size ();

    vector<string> generatedApplicationInstanceNames;

    for (i = 0; i < numberofValuesInRange; i++)
    {
        generatedApplicationInstanceNames.push_back (applicationInstanceNamePrefix + rangeVector[i]);
    }

    status = connection.registerExternalNonNativeServiceInstances (applicationName, generatedApplicationInstanceNames);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliGrapevineRootShell::registerServiceInstance : Successfully registered service instances." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliGrapevineRootShell::registerServiceInstance : Failed to register service instances. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliGrapevineRootShell::registerServiceInstancesByRangeHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE : register-service-instance <service-name> <service-instance-name-prefix> <Comma-Separated-Range>");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Registers an external non-native service instance with Service Coordinator.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "INPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  service-name");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Unique Name of the service ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  service-instance-name");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Unique Name of the service instance");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "  Comma-Separated-Range");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    A Comma separated range for instances to be combined with the prefix.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "OUTPUT :");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
}

}
