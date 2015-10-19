/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef SHELLWAVE_H
#define SHELLWAVE_H

#include "Shell/ShellBase.h"
#include "Shell/ShellRegression.h"
#include "Shell/ShellDebug.h"
#include "Shell/ShellTrace.h"
#include "Shell/ShellCluster.h"
#include "Shell/ShellWyser.h"
#include <string>

using namespace std;

namespace WaveNs
{

class ShellWave : public ShellBase
{
    private :
    protected :
    public :
                                    ShellWave                          (WaveObjectManager *pWaveObjectManager);
                                   ~ShellWave                          ();
        static  UI32                shellExecuteRegressionService       (UI32 argc, vector<string> argv);
        static  UI32                shellExecuteTraceService            (UI32 argc, vector<string> argv);
        static  UI32                shellExecuteDebugService            (UI32 argc, vector<string> argv);
    	static  UI32                shellExecuteClusterService          (UI32 argc, vector<string> argv);
    	static  UI32                shellExecuteWyserService            (UI32 argc, vector<string> argv);
        static  UI32                shellExecuteLoadScript              (UI32 argc, vector<string> argv);
        static  UI32                shellExecuteQuit                    (UI32 argc, vector<string> argv);
        static  UI32                shellExecuteHelp                    (UI32 argc, vector<string> argv);

        static  void                usageShellWaveRegressionService    ();
        static  void                usageShellWaveTraceService         ();
        static  void                usageShellWaveDebugService         ();
    	static  void                usageShellWaveClusterService       ();
    	static  void                usageShellWaveWyserService         ();
        static  void                usageShellWaveLoadScript           ();
        static  void                usageShellWaveHelp                 ();
        static  WaveMessageStatus   shellSendSynchronously              (WaveMessage *pWaveMessage);
        static  void                shellTrace                          (TraceLevel traceLevel, const string &stringToTrace);
                ShellRegression    *getRegressionShell                  ();
                ShellDebug         *getDebugShell                       ();
                ShellTrace         *getTraceShell                       ();
		        ShellCluster       *getClusterShell                     ();
		        ShellWyser         *getWyserShell                       ();

    private :
        ShellRegression                *m_pRegressionShell;
        ShellDebug                     *m_pDebugShell;
        ShellTrace                     *m_pTraceShell;
	    ShellCluster                   *m_pClusterShell;
        ShellWyser                     *m_pWyserShell;

    protected :
    public :

};

}

#endif //SHELLWAVE_H
