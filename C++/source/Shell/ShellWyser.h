/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef SHELLWYSER_H
#define SHELLWYSER_H

#include "Shell/ShellBase.h"
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{
extern "C" void addWyserFunction (ShellCmdFunction wyserFunction, const char *cliName);

class ShellWyser : public ShellBase
{
    private :
    protected :
    public :
                     ShellWyser             (WaveObjectManager *pWaveObjectManager);
                    ~ShellWyser             ();
        static UI32  shellExecuteHelpWyser  (UI32 argc, vector<string> argv);
        static UI32  shellExecuteQuitWyser  (UI32 argc, vector<string> argv);

        static void  usageShellWyserHelp   (void);
        static void  usageShellWyserQuit   (void);
        static void  registerWyserFunction (ShellCmdFunction wyserFunction, const char *cliName);

    private :
    protected :
    public :

};

}

#endif //SHELLDEBUG_H
