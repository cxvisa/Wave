/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/
#include "Shell/ShellObjectManager.h"
#include "Shell/ShellBase.h"
#include "Shell/ShellWave.h"

#include <string>

using namespace std;

namespace WaveNs
{

ShellWave::ShellWave (WaveObjectManager *pWaveObjectManager)
    :ShellBase (pWaveObjectManager, string("Wave"))
{
    addShellCommandHandler (ShellCommandHandler (string("regression"), 1,  (ShellCmdFunction) (&ShellWave::shellExecuteRegressionService), 1, (ShellUsageFunction) (&ShellWave::usageShellWaveRegressionService)));
    addShellCommandHandler (ShellCommandHandler (string("trace"),      1,  (ShellCmdFunction) (&ShellWave::shellExecuteTraceService),      1, (ShellUsageFunction) (&ShellWave::usageShellWaveTraceService)));
    addShellCommandHandler (ShellCommandHandler (string("debug"),      1,  (ShellCmdFunction) (&ShellWave::shellExecuteDebugService),      1, (ShellUsageFunction) (&ShellWave::usageShellWaveDebugService)));
    addShellCommandHandler (ShellCommandHandler (string("cluster"),    1,  (ShellCmdFunction) (&ShellWave::shellExecuteClusterService),    1, (ShellUsageFunction) (&ShellWave::usageShellWaveClusterService)));
    addShellCommandHandler (ShellCommandHandler (string("wyser"),      1,  (ShellCmdFunction) (&ShellWave::shellExecuteWyserService),      1, (ShellUsageFunction) (&ShellWave::usageShellWaveWyserService)));
    addShellCommandHandler (ShellCommandHandler (string("load"),       2,  (ShellCmdFunction) (&ShellWave::shellExecuteLoadScript),        1, (ShellUsageFunction) (&ShellWave::usageShellWaveLoadScript)));
    addShellCommandHandler (ShellCommandHandler (string("help"),       1,  (ShellCmdFunction) (&ShellWave::shellExecuteHelp),              1, (ShellUsageFunction) (&ShellWave::usageShellWaveHelp)));
    addShellCommandHandler (ShellCommandHandler (string("QUIT"),       1,  (ShellCmdFunction) (&ShellWave::shellExecuteQuit),              1, NULL));

    m_pRegressionShell  =   new ShellRegression    (pWaveObjectManager);
    m_pDebugShell       =   new ShellDebug         (pWaveObjectManager);
    m_pTraceShell       =   new ShellTrace         (pWaveObjectManager);
    m_pClusterShell     =   new ShellCluster       (pWaveObjectManager);
    m_pWyserShell       =   new ShellWyser         (pWaveObjectManager);
}


ShellWave::~ShellWave ()
{

    if (NULL != m_pRegressionShell)
    {
        delete m_pRegressionShell;
    }

    if (NULL != m_pDebugShell)
    {
        delete m_pDebugShell;
    }

    if (NULL != m_pTraceShell)
    {
        delete m_pTraceShell;
    }

    if (NULL != m_pClusterShell) 
    {
	    delete m_pClusterShell;
    }
    
    if (NULL != m_pWyserShell) 
    {
	    delete m_pWyserShell;
    }
}

ShellRegression *ShellWave::getRegressionShell ()
{
    return (m_pRegressionShell);
}

ShellDebug *ShellWave::getDebugShell ()
{
    return (m_pDebugShell);
}

ShellTrace *ShellWave::getTraceShell ()
{
    return (m_pTraceShell);
}

ShellCluster *ShellWave::getClusterShell()
{
    return (m_pClusterShell);
}

ShellWyser *ShellWave::getWyserShell()
{
    return (m_pWyserShell);
}

UI32 ShellWave::shellExecuteRegressionService (UI32 argc, vector<string> argv)
{
    shellTrace (TRACE_LEVEL_DEVEL, "ShellWave::shellExecuteRegressionService : Entering ...");

    (ShellObjectManager::getInstance ())->m_pWaveShell->m_pRegressionShell->shellGetServicesList ();
    (ShellObjectManager::getInstance ())->m_pWaveShell->m_pRegressionShell->shellExecuteHandler ();
    return SHELL_OK;
}

UI32 ShellWave::shellExecuteTraceService (UI32 argc, vector<string> argv)
{
    shellTrace (TRACE_LEVEL_DEVEL, "ShellWave::shellExecuteTraceService : Entering ...");

    (ShellObjectManager::getInstance ())->m_pWaveShell->m_pTraceShell->shellGetServicesList ();
    (ShellObjectManager::getInstance ())->m_pWaveShell->m_pTraceShell->shellExecuteHandler ();
    return SHELL_OK;
}

UI32 ShellWave::shellExecuteDebugService (UI32 argc, vector<string> argv)
{
    shellTrace (TRACE_LEVEL_DEVEL, "ShellWave::shellExecuteDebugService : Entering ...");

    (ShellObjectManager::getInstance ())->m_pWaveShell->m_pDebugShell->shellExecuteHandler ();
    return SHELL_OK;
}

UI32 ShellWave::shellExecuteClusterService (UI32 argc, vector<string> argv)
{
    shellTrace (TRACE_LEVEL_DEVEL, "ShellWave::shellExecuteClusterService : Entering ...");

    (ShellObjectManager::getInstance ())->m_pWaveShell->m_pClusterShell->shellExecuteHandler ();
    return SHELL_OK;
}

UI32 ShellWave::shellExecuteWyserService (UI32 argc, vector<string> argv)
{
    shellTrace (TRACE_LEVEL_DEVEL, "ShellWave::shellExecuteWyserService : Entering ...");

    (ShellObjectManager::getInstance ())->m_pWaveShell->m_pWyserShell->shellExecuteHandler ();
    return SHELL_OK;
}

UI32 ShellWave::shellExecuteLoadScript (UI32 argc, vector<string> argv)
{
    (ShellObjectManager::getInstance ())->m_inputSource.open (argv [1].c_str (), ifstream::in);
    return SHELL_OK;
}

UI32 ShellWave::shellExecuteHelp (UI32 argc, vector<string> argv)
{
    shellTrace (TRACE_LEVEL_DEVEL, "ShellWave::shellExecuteHelp : Entering ...");

    cout << endl << "Size of Wave Msg: " << sizeof(WaveMessage) << endl;
    usageShellWaveHelp ();
    return SHELL_OK;
}

UI32 ShellWave::shellExecuteQuit (UI32 argc, vector<string> argv)
{
    shellTrace (TRACE_LEVEL_DEVEL, "ShellWave::shellExecuteQuit : Entering ...");
    exit (0);
}

void ShellWave::usageShellWaveRegressionService ()
{
    cout << "regression                 <Start regression shell>" << endl;
}

void ShellWave::usageShellWaveTraceService ()
{
    cout << "trace                      <Start trace shell>" << endl;
}

void ShellWave::usageShellWaveDebugService ()
{
    cout << "debug                      <Start debug shell>" << endl;
}

void ShellWave::usageShellWaveClusterService ()
{
    cout<<"cluster                     <Start cluster shell>"<< endl;
}

void ShellWave::usageShellWaveWyserService ()
{
    cout<<"wyser                       <Start wyser shell>"<< endl;
}

void ShellWave::usageShellWaveLoadScript ()
{
    cout << "load <filename>            <Load Script>" << endl;
}

void ShellWave::usageShellWaveHelp ()
{
    usageShellWaveRegressionService ();
    usageShellWaveTraceService ();
    usageShellWaveDebugService ();
    usageShellWaveLoadScript ();
    usageShellWaveClusterService ();
    usageShellWaveWyserService ();
    cout << "help                       <Help for wave shell>" << endl;
}


WaveMessageStatus ShellWave::shellSendSynchronously (WaveMessage *pWaveMessage)
{
    return ((ShellObjectManager::getInstance ())->m_pWaveShell->sendSynchronously (pWaveMessage));
}

void  ShellWave::shellTrace (TraceLevel shellTraceLevel, const string &stringToTrace)
{
    return (ShellObjectManager::getInstance ())->m_pWaveShell->trace (shellTraceLevel, stringToTrace);
}

}
