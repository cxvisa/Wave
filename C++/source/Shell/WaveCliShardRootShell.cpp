/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Shell/WaveCliShardRootShell.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

#include <stdlib.h>

namespace WaveNs
{

WaveCliShardRootShell::WaveCliShardRootShell (WaveClientSynchronousConnection &connection)
    : WaveCliShell ("shard", connection)
{
    addCommandfunction ("register-service",                      reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardRootShell::registerService),                   "Registers a shard service.",                       reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardRootShell::registerServiceHelp));
    addCommandfunction ("register-services-by-range",            reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardRootShell::registerServicesByRange),           "Registers shard services using range",             reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardRootShell::registerServicesByRangeHelp));

    addCommandfunction ("register-service-instance",             reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardRootShell::registerServiceInstance),           "Registers a shard service instance.",              reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardRootShell::registerServiceInstanceHelp));
    addCommandfunction ("register-service-instances-by-range",   reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardRootShell::registerServiceInstancesByRange),   "Registers shard service instances using range",    reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardRootShell::registerServiceInstancesByRangeHelp));

    addCommandfunction ("unregister-service-instance",           reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardRootShell::unregisterServiceInstance),         "Un-Registers a shard service instance.",           reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardRootShell::unregisterServiceInstanceHelp));
    addCommandfunction ("unregister-service-instances-by-range", reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardRootShell::unregisterServiceInstancesByRange), "Un-Registers shard service instances using range", reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardRootShell::unregisterServiceInstancesByRangeHelp));
}

WaveCliShardRootShell::~WaveCliShardRootShell ()
{
}

void WaveCliShardRootShell::briefHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Shard interaction with Service Coordinator for service / service-instance management.");
}

ResourceId WaveCliShardRootShell::registerService (const vector<string> &arguments)
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
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardRootShell::showRunningConfiguration : Successfully registered services." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "Failed to Obtain the Managed Objects. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardRootShell::registerServiceHelp ()
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

ResourceId WaveCliShardRootShell::registerServicesByRange (const vector<string> &arguments)
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
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardRootShell::showRunningConfiguration : Successfully registered services." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "Failed to Obtain the Managed Objects. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardRootShell::registerServicesByRangeHelp ()
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

ResourceId WaveCliShardRootShell::registerServiceInstance (const vector<string> &arguments)
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
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardRootShell::registerServiceInstance : Successfully registered service instance." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliShardRootShell::registerServiceInstance : Failed to register service instance. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardRootShell::registerServiceInstanceHelp ()
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

ResourceId WaveCliShardRootShell::registerServiceInstancesByRange (const vector<string> &arguments)
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
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardRootShell::registerServiceInstance : Successfully registered service instances." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliShardRootShell::registerServiceInstance : Failed to register service instances. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardRootShell::registerServiceInstancesByRangeHelp ()
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

ResourceId WaveCliShardRootShell::unregisterServiceInstance (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (2 > (arguments.size ()))
    {
        registerServiceHelp ();

        return (status);
    }

    status = connection.unregisterExternalNonNativeServiceInstance (arguments[0], arguments[1]);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardRootShell::unregisterServiceInstance : Successfully unregistered service instance." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliShardRootShell::unregisterServiceInstance : Failed to unregister service instance. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardRootShell::unregisterServiceInstanceHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE : unregister-service-instance <service-name> <service-instance-name>");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    U-Registers an external non-native service instance with Service Coordinator.");
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

ResourceId WaveCliShardRootShell::unregisterServiceInstancesByRange (const vector<string> &arguments)
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

    status = connection.unregisterExternalNonNativeServiceInstances (applicationName, generatedApplicationInstanceNames);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardRootShell::unregisterServiceInstance : Successfully registered service instances." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliShardRootShell::unregisterServiceInstance : Failed to register service instances. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardRootShell::unregisterServiceInstancesByRangeHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE : unregister-service-instance <service-name> <service-instance-name-prefix> <Comma-Separated-Range>");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "    Un-Registers an external non-native service instance with Service Coordinator.");
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
