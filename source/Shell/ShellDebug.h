/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef SHELLDEBUG_H
#define SHELLDEBUG_H

#include "Shell/ShellBase.h"
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{
extern "C" void addDebugFunction (ShellCmdFunction debugFunction, const char *debugName);

class ShellDebug : public ShellBase
{
    private :
    protected :
    public :
                     ShellDebug            (WaveObjectManager *pWaveObjectManager);
                    ~ShellDebug            ();
        static UI32  shellExecuteHelpDebug (UI32 argc, vector<string> argv);
        static UI32  shellExecuteQuitDebug (UI32 argc, vector<string> argv);

        static void  usageShellDebugHelp   (void);
        static void  usageShellDebugQuit   (void);
        static void  registerDebugFunction (ShellCmdFunction debugFunction, const char *debugName);

    private :
    protected :
    public :

};

}

#endif //SHELLDEBUG_H
