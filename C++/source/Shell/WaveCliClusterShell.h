/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLICLUSTERSHELL_H
#define WAVECLICLUSTERSHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliClusterShell : public WaveCliShell
{
    private :
                   WaveCliClusterShell (WaveClientSynchronousConnection &connection);

        void       briefHelp           ();

        ResourceId clusterCreate       (const vector<string> &arguments);
        ResourceId getHeartBeatStats   (const vector<string> &arguments);
        void       clusterCreateHelp   (void);

    protected :
    public :
        virtual ~WaveCliClusterShell ();

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLICLUSTERSHELL_H
