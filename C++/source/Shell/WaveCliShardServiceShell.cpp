/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Shell/WaveCliShardServiceShell.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

#include <stdlib.h>

namespace WaveNs
{

WaveCliShardServiceShell::WaveCliShardServiceShell (WaveClientSynchronousConnection &connection)
    : WaveCliShell ("shard-service", connection)
{
    addCommandfunction ("configure-service-shell",                         reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardServiceShell::configureServiceShell),                       "Configures a shard service shell.",                         reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardServiceShell::configureServiceShellHelp));

    addCommandfunction ("register-service-instance-sharding-capabilities", reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardServiceShell::registerServiceInstanceShardingCapabilities), "Registers a shard service instance sharding capabilities.", reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardServiceShell::registerServiceInstanceShardingCapabilitiesHelp));

    addCommandfunction ("get-shard-owner-for-resource",                    reinterpret_cast<WaveShellCommandFunction> (&WaveCliShardServiceShell::getShardOwnerForResource),                    "Gets the shard owner for the given resource.",                  reinterpret_cast<WaveShellCommandHelpFunction> (&WaveCliShardServiceShell::getShardOwnerForResourceHelp));
}

WaveCliShardServiceShell::~WaveCliShardServiceShell ()
{
}

void WaveCliShardServiceShell::briefHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Shard interaction with Service Coordinator for service / service-instance management.");
}

ResourceId WaveCliShardServiceShell::configureServiceShell (const vector<string> &arguments)
{
    ResourceId status = WAVE_MESSAGE_SUCCESS;

    if (1 < (arguments.size ()))
    {
        m_serviceName         = arguments[0];
        m_serviceInstanceName = arguments[1];

        setShellName (m_serviceName + " / " + m_serviceInstanceName);
    }
    else
    {
        configureServiceShellHelp ();
    }

    return (status);
}

void WaveCliShardServiceShell::configureServiceShellHelp ()
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

ResourceId WaveCliShardServiceShell::registerServiceInstanceShardingCapabilities (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (0 > (arguments.size ()))
    {
        registerServiceInstanceShardingCapabilitiesHelp ();

        return (status);
    }

    vector<string> shardingCpaabilities = arguments;

    status = connection.registerExternalNonNativeServiceInstanceShardingCapabilities (m_serviceName, m_serviceInstanceName, shardingCpaabilities);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardServiceShell::registerServiceInstanceShardingCapabilities : Successfully configured service instance sharding capabilities." ));
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliShardServiceShell::registerServiceInstanceShardingCapabilities : Failed to configure service instance sharding capabilities. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardServiceShell::registerServiceInstanceShardingCapabilitiesHelp ()
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

ResourceId WaveCliShardServiceShell::getShardOwnerForResource (const vector<string> &arguments)
{
    ResourceId                      status                 = WAVE_MESSAGE_ERROR;
    WaveClientSynchronousConnection connection             = getConnection ();

    if (3 > (arguments.size ()))
    {
        getShardOwnerForResourceHelp ();

        return (status);
    }

    const string    shardingCategory   = arguments[0];
    const string    resourceNamePrefix = arguments[1];
    const string    resourceRange      = arguments[2];
    const UI32Range range                (resourceRange);
          UI32      i                  = 0;

          vector<UI32> rangeVector;

    range.getUI32RangeVector (rangeVector);

    const UI32 numberofValuesInRange = rangeVector.size ();

    vector<string> generatedResourceNames;

    for (i = 0; i < numberofValuesInRange; i++)
    {
        generatedResourceNames.push_back (resourceNamePrefix + rangeVector[i]);
    }

    vector<string> serviceInstanceNames;

    status = connection.requestForShardOwnerForResources (shardingCategory, generatedResourceNames, serviceInstanceNames);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        trace (TRACE_LEVEL_INFO, string ("WaveCliShardServiceShell::getShardOwnerForResource : Successfully requested for shard owner." ));

        const UI32 numberOfResourcesNames       = generatedResourceNames.size ();
        const UI32 numberOfServiceInstanceNames = serviceInstanceNames.size   ();

        waveAssert (numberOfResourcesNames == numberOfServiceInstanceNames, __FILE__, __LINE__);

        for (i = 0; i < numberOfResourcesNames; i++)
        {
            tracePrintf (TRACE_LEVEL_INFO, true, false, "WaveCliShardServiceShell::getShardOwnerForResource : Shard Owner for %s : %s", generatedResourceNames[i].c_str (), serviceInstanceNames[i].c_str ());
        }
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "WaveCliShardServiceShell::getShardOwnerForResource : Failed to request for shard owner. Status : " + FrameworkToolKit::localize (status));
    }

    return (status);
}

void WaveCliShardServiceShell::getShardOwnerForResourceHelp ()
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
