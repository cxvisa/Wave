/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef SHELLREGRESSION_H
#define SHELLREGRESSION_H

#include "Shell/ShellBase.h"
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class ShellRegression : public ShellBase
{
    private :
    protected :
    public :
                ShellRegression                             (WaveObjectManager *pWaveObjectManager);
               ~ShellRegression                             ();
        static  UI32    shellExecuteListServices            (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteSetServiceState         (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteSetAllServicesState     (UI32 argc, vector<string> argv);
        static  UI32    shellExecutePrepareRegression       (UI32 argc, vector<string> argv);
        static  UI32    shellExecutePrepareRegression2      (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteStartRegression         (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteRunTestService          (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteQuitRegression          (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteHelpRegression          (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteSetDefaultState         (UI32 argc, vector<string> argv);

                UI32    listServices                        (UI32 argc, vector<string> argv);
                UI32    setServiceState                     (UI32 argc, vector<string> argv);
                UI32    setAllServicesState                 (UI32 argc, vector<string> argv);
                UI32    prepareRegression                   (UI32 argc, vector<string> argv);
                UI32    prepareRegression2                  (UI32 argc, vector<string> argv);
                UI32    startRegression                     (UI32 argc, vector<string> argv);
                UI32    runTestService                      (UI32 argc, vector<string> argv);
                UI32    quitRegression                      (UI32 argc, vector<string> argv);
                UI32    helpRegression                      (UI32 argc, vector<string> argv);
                UI32    setDefaultState                     (UI32 argc, vector<string> argv);

                void    shellGetServicesList                (void);

        static  void    usageShellRegressionList            (void);
        static  void    usageShellRegressionSetState        (void);
        static  void    usageShellRegressionSetAllStates    (void);
        static  void    usageShellRegressionStart           (void);
        static  void    usageShellRegressionPrepare         (void);
        static  void    usageShellRegressionPrepare2        (void);
        static  void    usageShellRegressionRun             (void);
        static  void    usageShellRegressionHelp            (void);
        static  void    usageShellRegressionQuit            (void);
        static  void    usageShellRegressionSetDefaultState (void);

                    // Now the data members

    private :
                vector<WaveServiceId> m_serviceMap;
                UI32                   m_nServices;
    protected :
    public :
};

}

#endif //SHELLREGRESSION_H
