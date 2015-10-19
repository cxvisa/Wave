/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/
#include "Shell/ShellObjectManager.h"
#include "Shell/ShellDebug.h"
#include "Framework/Postboot/WavePostbootDebug.h"
#include "Framework/Postboot/WavePostbootAgent.h"
#include "Framework/Postboot/WavePostbootMessages.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

WavePostbootDebug::WavePostbootDebug  ()
{
}

WavePostbootDebug::~WavePostbootDebug  ()
{
}

void WavePostbootDebug::initialize ()
{
    addDebugFunction ((ShellCmdFunction) (&WavePostbootDebug::shellExecuteTriggerPostbootPasses), "startPostbootPasses");
}

UI32 WavePostbootDebug::shellExecuteTriggerPostbootPasses (UI32 argc, vector<string> argv)
{
    ExecutePostbootPassTableMessage *pMessage;

    pMessage = new ExecutePostbootPassTableMessage();
    ShellWave::shellSendSynchronously (pMessage);
    delete (pMessage);

    return SHELL_OK;
}

}
