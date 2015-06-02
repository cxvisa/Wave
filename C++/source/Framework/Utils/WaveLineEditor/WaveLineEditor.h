/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVELINEEDITOR_H
#define WAVELINEEDITOR_H

#include "Framework/Types/Types.h"
#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveLineEditor
{
    private :
        UI32 getNumberOfCharactersAvailableToRead ();

    protected :
    public :
                WaveLineEditor   ();
                WaveLineEditor   (const vector<string> &validCommands);
               ~WaveLineEditor   ();

        string  getUserInputLine (const string &linePrompt);

        void    addValidCommand  (const string &validCommands);

    // Now the data members

    private :
        vector<string> m_validCommands;
        vector<string> m_commandHistory;

    protected :
    public :
};

}

#endif // WAVELINEEDITOR_H
