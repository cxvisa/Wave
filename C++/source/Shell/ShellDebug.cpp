/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#include "Shell/ShellDebug.h"
#include "ShellTypes.h"
#include <string>
#include "Shell/ShellObjectManager.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

ShellDebug::ShellDebug (WaveObjectManager *pWaveObjectManager)
    :ShellBase (pWaveObjectManager, string("Debug"))
{
    addShellCommandHandler (ShellCommandHandler (string("regression"), 1,  (ShellCmdFunction) (&ShellPrism::shellExecuteRegressionService), 1, (ShellUsageFunction) (&ShellPrism::usageShellPrismRegressionService)));
    addShellCommandHandler (ShellCommandHandler (string("trace"),      1,  (ShellCmdFunction) (&ShellPrism::shellExecuteTraceService),      1, (ShellUsageFunction) (&ShellPrism::usageShellPrismTraceService)));
    addShellCommandHandler (ShellCommandHandler (string("help"),       1,  (ShellCmdFunction) (&ShellDebug::shellExecuteHelpDebug),         1, (ShellUsageFunction) (&ShellDebug::usageShellDebugHelp)));
    addShellCommandHandler (ShellCommandHandler (string("quit"),       1,  (ShellCmdFunction) (&ShellDebug::shellExecuteQuitDebug),         1, (ShellUsageFunction) (&ShellDebug::usageShellDebugQuit)));
}

ShellDebug::~ShellDebug ()
{
}

UI32 ShellDebug::shellExecuteHelpDebug (UI32 argc, vector<string> argv)
{
    ShellPrism::shellTrace (TRACE_LEVEL_DEVEL, "ShellDebug::shellExecuteHelpDebug : Entering ...");

    usageShellDebugHelp ();

    return SHELL_OK;
}

UI32 ShellDebug::shellExecuteQuitDebug (UI32 argc, vector<string> argv)
{
    return SHELL_EXIT;
}

void ShellDebug::usageShellDebugQuit (void)
{
    cout << "quit                                           <Quit debug shell>" << endl;
}


void ShellDebug::usageShellDebugHelp (void)
{
}


void ShellDebug::registerDebugFunction (ShellCmdFunction debugFunction, const char *debugName)
{
    static  WaveMutex mutex;

    mutex.lock();
    ((ShellObjectManager::getInstance ())->m_pPrismShell->getDebugShell ())->addShellCommandHandler (ShellCommandHandler (string(debugName), 1,  debugFunction, strlen (debugName), NULL));
    mutex.unlock();
}

extern "C" void addDebugFunction (ShellCmdFunction debugFunction, const char *debugName)
{
    WaveManagementInterfaceRole waveManagementInterfaceRole = FrameworkToolKit::getManagementInterfaceRole ();

    if (WAVE_MGMT_INTF_ROLE_CLI != waveManagementInterfaceRole)
    {
        ShellDebug::registerDebugFunction (debugFunction, debugName);
    }
}

}
