/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLISERVICESHELL_H
#define WAVECLISERVICESHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliServiceShell : public WaveCliShell
{
    private :
                   WaveCliServiceShell   (WaveClientSynchronousConnection &connection);

        void       briefHelp                 ();

        ResourceId serviceList               (const vector<string> &arguments);
        void       serviceListHelp           (void);

        ResourceId serviceSetCpuAffinity     (const vector<string> &arguments);
        void       serviceSetCpuAffinityHelp (void);

        ResourceId clientList               (const vector<string> &arguments);
        void       clientListHelp           (void);

    protected :
    public :
        virtual ~WaveCliServiceShell ();

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLISERVICESHELL_H
