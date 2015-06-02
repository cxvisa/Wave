/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVECLIWYSERSHELL_H
#define WAVECLIWYSERSHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliWyserShell : public WaveCliShell
{
    private :
                   WaveCliWyserShell (WaveClientSynchronousConnection &connection);

        void       briefHelp           ();
        void       wyserCreateHelp   (void);


    protected :
    public :
        virtual        ~WaveCliWyserShell ();
        ResourceId      rebuildYangInterfaces (const vector<string> &arguments);

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLIWyserSHELL_H
