/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "ManagementInterface/ClientInterface/WaveUserInterfaceObjectManager.h"

#include <stdarg.h>

namespace WaveNs
{

void trace (TraceLevel traceLevel, const string &stringToTrace)
{
    WaveManagementInterfaceRole waveManagementInterfaceRole = FrameworkToolKit::getManagementInterfaceRole ();

    if ((WAVE_MGMT_INTF_ROLE_SERVER == waveManagementInterfaceRole) || (WAVE_MGMT_INTF_ROLE_CLI == waveManagementInterfaceRole))
    {
        (WaveFrameworkObjectManager::getInstance ())->trace (traceLevel, stringToTrace);
    }
    else
    {
        (WaveUserInterfaceObjectManager::getInstance ())->trace (traceLevel, stringToTrace);
    }
}

void tracePrintf (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...)
{
    va_list variableArguments;

    va_start (variableArguments, pFormat);

    WaveManagementInterfaceRole waveManagementInterfaceRole = FrameworkToolKit::getManagementInterfaceRole ();

    if ((WAVE_MGMT_INTF_ROLE_SERVER == waveManagementInterfaceRole) || (WAVE_MGMT_INTF_ROLE_CLI == waveManagementInterfaceRole))
    {
        (WaveFrameworkObjectManager::getInstance ())->tracePrintf (traceLevel, addNewLine, suppressPrefix, pFormat, variableArguments);
    }
    else
    {
        (WaveUserInterfaceObjectManager::getInstance ())->tracePrintf (traceLevel, addNewLine, suppressPrefix, pFormat, variableArguments);
    }

    va_end (variableArguments);
}

void tracePrintf (TraceLevel traceLevel, const char * const pFormat, ...)
{
    va_list variableArguments;

    va_start (variableArguments, pFormat);

    WaveManagementInterfaceRole waveManagementInterfaceRole = FrameworkToolKit::getManagementInterfaceRole ();

    if ((WAVE_MGMT_INTF_ROLE_SERVER == waveManagementInterfaceRole) || (WAVE_MGMT_INTF_ROLE_CLI == waveManagementInterfaceRole))
    {
        (WaveFrameworkObjectManager::getInstance ())->tracePrintf (traceLevel, pFormat, variableArguments);
    }
    else
    {
        (WaveUserInterfaceObjectManager::getInstance ())->tracePrintf (traceLevel, pFormat, variableArguments);
    }

    va_end (variableArguments);
}

}
