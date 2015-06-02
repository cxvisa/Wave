/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIREGRESSIONSHELL_H
#define WAVECLIREGRESSIONSHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliRegressionShell : public WaveCliShell
{
    private :
                   WaveCliRegressionShell       (WaveClientSynchronousConnection &connection);

        void       briefHelp                    ();

        ResourceId regressionList               (const vector<string> &arguments);
        void       regressionListHelp           (void);

        ResourceId regressionPrepare2           (const vector<string> &arguments);
        void       regressionPrepare2Help       (void);

        ResourceId regressionRunForAService     (const vector<string> &arguments);
        void       regressionRunForAServiceHelp (void);

    protected :
    public :
        virtual ~WaveCliRegressionShell ();

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLIREGRESSIONSHELL_H
