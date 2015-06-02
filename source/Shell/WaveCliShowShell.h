/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLISHOWSHELL_H
#define WAVECLISHOWSHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliShowShell : public WaveCliShell
{
    private :
                   WaveCliShowShell             (WaveClientSynchronousConnection &connection);

        void       briefHelp                    ();

        ResourceId showRunningConfiguration                        (const vector<string> &arguments);
        void       showRunningConfigurationHelp                    (void);
        ResourceId showRunningConfigurationByQualifiedYangPath     (const vector<string> &arguments);
        void       showRunningConfigurationByQualifiedYangPathHelp (void);

    protected :
    public :
        virtual ~WaveCliShowShell ();

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLISHOWSHELL_H
