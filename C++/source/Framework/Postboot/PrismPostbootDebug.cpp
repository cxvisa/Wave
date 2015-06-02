/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/
#include "Shell/ShellObjectManager.h"
#include "Shell/ShellDebug.h"
#include "Framework/Postboot/PrismPostbootDebug.h"
#include "Framework/Postboot/PrismPostbootAgent.h"
#include "Framework/Postboot/PrismPostbootMessages.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

PrismPostbootDebug::PrismPostbootDebug  ()
{
}

PrismPostbootDebug::~PrismPostbootDebug  ()
{
}

void PrismPostbootDebug::initialize ()
{
    addDebugFunction ((ShellCmdFunction) (&PrismPostbootDebug::shellExecuteTriggerPostbootPasses), "startPostbootPasses");
}

UI32 PrismPostbootDebug::shellExecuteTriggerPostbootPasses (UI32 argc, vector<string> argv)
{
    ExecutePostbootPassTableMessage *pMessage;

    pMessage = new ExecutePostbootPassTableMessage();
    ShellPrism::shellSendSynchronously (pMessage);
    delete (pMessage);

    return SHELL_OK;
}

}
