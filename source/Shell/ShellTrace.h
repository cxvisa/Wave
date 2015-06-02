/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef SHELLTRACE_H
#define SHELLTRACE_H

#include "Shell/ShellBase.h"
#include <string>

using namespace std;

namespace WaveNs
{

class ShellTrace : public ShellBase
{
    private :
    protected :
    public :
                        ShellTrace                              (WaveObjectManager *pWaveObjectManager);
                       ~ShellTrace                              ();
        static  UI32    shellExecuteListServices                (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteSetTraceLevel               (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteSetAllServicesTraceLevel    (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteQuitTrace                   (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteHelpTrace                   (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteSetDefaultLevels            (UI32 argc, vector<string> argv);
        static  UI32    shellExecuteLegend                      (UI32 argc, vector<string> argv);

                UI32    listServices                            (UI32 argc, vector<string> argv);
                UI32    setServiceLevel                         (UI32 argc, vector<string> argv);
                UI32    setAllServicesLevel                     (UI32 argc, vector<string> argv);
                UI32    quitTrace                               (UI32 argc, vector<string> argv);
                UI32    helpTrace                               (UI32 argc, vector<string> argv);
                UI32    setDefaultLevels                        (UI32 argc, vector<string> argv);
                UI32    legend                                  (UI32 argc, vector<string> argv);

                void    shellGetServicesList                    (void);

        static  void    usageShellTraceList                     (void);
        static  void    usageShellTraceSetLevel                 (void);
        static  void    usageShellTraceSetAllServicesTraceLevel (void);
        static  void    usageShellTraceHelp                     (void);
        static  void    usageShellTraceQuit                     (void);
        static  void    usageShellTraceSetDefaultLevels         (void);
        static  void    usageShellLegend                        (void);


                    // Now the data members
    private :
        vector<TraceClientId> m_serviceMap;
        UI32                  m_nServices;

    protected :
    public :

};

}

#endif //SHELLTRACE_H
