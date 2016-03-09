/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESHELL_H
#define WAVESHELL_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveLineEditor/WaveLineEditor.h"

#include <string>
#include <map>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveShell;

typedef ResourceId (WaveShell::* WaveShellCommandFunction)     (const vector<string> &arguments);
typedef void       (WaveShell::* WaveShellCommandHelpFunction) ();

class WaveShell
{
    private :
        virtual void briefHelp   ();
                void overAllHelp (const vector<string> &arguments);
                void help        (const string &command);

    protected :
        void runCommand      (const vector<string> &arguments, const bool &exitWhenDone);
        bool isAKnownCommand (const string &command);

    public :
                        WaveShell          (const string &shellName);

        virtual        ~WaveShell          ();

                string  getShellName       () const;
                void    setShellName       (const string &shellName);

                void    addCommandfunction (const string &command, WaveShellCommandFunction commandFunction, const string &commandBriefHelp, WaveShellCommandHelpFunction commandHelpFunction = NULL, WaveShell *pCommandFunctionOwner = NULL);
                void    addSubShell        (WaveShell *pSubshell);

                void    execute            (const vector<string> &arguments);

    // Now the data members

    private :
        string                                    m_shellName;
        map<string, WaveShell *>                  m_subShells;
        map<string, WaveShellCommandFunction>     m_commandFunctions;
        map<string, WaveShellCommandHelpFunction> m_commandHelpFunctions;
        map<string, string>                       m_commandFunctionBriefDescriptions;
        map<string, WaveShell *>                  m_commandFunctionOwners;

        WaveLineEditor                            m_waveLineEditor;

    protected :
    public :
};

}

#endif // WAVESHELL_H
