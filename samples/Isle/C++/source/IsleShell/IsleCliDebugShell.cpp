/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "IsleShell/IsleCliDebugShell.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace IsleNs
{

IsleCliDebugShell::IsleCliDebugShell (IsleClientSynchronousConnection &connection)
    : WaveCliShell                      ("isledebug", connection),
      m_isleClientSynchronousConnection (connection)
{
}

IsleCliDebugShell::~IsleCliDebugShell ()
{
}

IsleClientSynchronousConnection &IsleCliDebugShell::getIsleClientSynchronousConnection ()
{
    return (m_isleClientSynchronousConnection);
}

void IsleCliDebugShell::briefHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Debug shell provides a way to execute debug actions.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Developer can execute pre-registered actions from this shell.");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Debug actions that are not particularly part of any other shells");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        typically land here.");
}

}

