/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Shell/WaveCliWyserShell.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

#include <stdlib.h>

namespace WaveNs
{

WaveCliWyserShell::WaveCliWyserShell (WaveClientSynchronousConnection &connection)
    : WaveCliShell ("wyser", connection)
{
    addCommandfunction ("rebuildYangInterfaces", reinterpret_cast<WaveShellCommandFunction> (&WaveCliWyserShell::rebuildYangInterfaces),  "rebuild yang interfaces", NULL);
}

WaveCliWyserShell::~WaveCliWyserShell ()
{
}

void WaveCliWyserShell::briefHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        Wyser shell provides basic control to run wyser based internal");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        commands in Wave based application.  For more information on");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "        configuring Wyser, please type help in Wyser shell");
}

void WaveCliWyserShell::wyserCreateHelp ()
{
    tracePrintf (TRACE_LEVEL_INFO, true, true, "USAGE : ");
    tracePrintf (TRACE_LEVEL_INFO, true, true, "");
}

ResourceId WaveCliWyserShell::rebuildYangInterfaces (const vector<string> &arguments)
{
    ResourceId                      status;
    WaveClientSynchronousConnection  connection  = getConnection ();

    status = connection.rebuildYangInterfaces ();

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        return (WAVE_MESSAGE_SUCCESS);
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "DcmCliDebugShell::rebuildYangInterfaces : Rebuilding Yang Interfaces Failed with error status : " + FrameworkToolKit::localize (status));
    }

    return (WAVE_MESSAGE_ERROR);
}

}
