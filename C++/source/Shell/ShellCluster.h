/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                                    *
 ***************************************************************************/

#ifndef SHELLCLUSTER_H
#define SHELLCLUSTER_H

#include "Shell/ShellBase.h"
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

//
// registers the cli command handler against the cliname 
//
extern "C" void addClusterFunction (ShellCmdFunction clusterFunction, const char *cliName);


///Class:
///ShellCluster
///Description:
/// This Class represents the Cluster Subshell
/// It provides the interface fro cluster CLIs
class ShellCluster : public ShellBase
{
    private :
    protected :
    public :
                     ShellCluster            (WaveObjectManager *pWaveObjectManager);
                    ~ShellCluster            ();
        static UI32  shellExecuteHelpCluster (UI32 argc, vector<string> argv);
        static UI32  shellExecuteQuitCluster (UI32 argc, vector<string> argv);

        static void  usageShellClusterHelp   (void);
        static void  usageShellClusterQuit   (void);
        static void  registerClusterFunction (ShellCmdFunction cliFunction, const char *cliName);

    private :
    protected :
    public :

};

}

#endif //SHELLCLUSTER_H
