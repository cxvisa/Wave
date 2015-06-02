/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef SHELLBASE_H
#define SHELLBASE_H

#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/WaveLineEditor/WaveLineEditor.h"
#include "ShellTypes.h"
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class ShellBase;
class ShellCommandHandler;

typedef UI32 (*ShellCmdFunction)   (UI32 argc, vector<string> argv);
typedef UI32 (*ShellUsageFunction) ();

class ShellBase : public WaveWorker
{
    private :
        void    getArguments (string *cmdString, vector<string> &argv, UI32 *argc);

    protected :
    public :
        void    shellExecuteHandler    (void);
                ShellBase              (WaveObjectManager *pWaveObjectManager, string shellName);
               ~ShellBase              ();
        void    setShellCommandHandler (vector<ShellCommandHandler>    *shellCommandHandler);

        string  getShellName           () const;

        void    addShellCommandHandler (const ShellCommandHandler &shellCommandHandler);

    // Now the data members

    private :
        string                      m_shellName;
        vector<ShellCommandHandler> m_shellCommandHandlers;
        WaveLineEditor              m_waveLineEditor;

    protected :
    public :

};

class ShellCommandHandler
{

    private :
    protected :
    public :
                                ShellCommandHandler (string action, UI32 minArgc, ShellCmdFunction cmdFunction, UI32 minCmdLength, ShellUsageFunction usageFunction);
                                ShellCommandHandler ();
                               ~ShellCommandHandler ();
        string                  getAction           () const;
        UI32                    getMinArgc          () const;
        ShellCmdFunction        getCmdFunction      () const;
        ShellUsageFunction      getUsageFunction    () const;
        UI32                    getMinCmdLength     () const;
        ShellCommandHandler     &operator =         (const ShellCommandHandler &rhs);

    // Now the data members

    private :
        string                  m_action;
        UI32                    m_minArgc;
        ShellCmdFunction        m_cmdFunction;
        UI32                    m_minCmdLength;
        ShellUsageFunction      m_usageFunction;

    protected :
    public :

};


}
#endif //SHELLBASE_H
