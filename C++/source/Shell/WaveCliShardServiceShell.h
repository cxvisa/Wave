/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLISHARDSERVICESHELL_H
#define WAVECLISHARDSERVICESHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliShardServiceShell : public WaveCliShell
{
    private :
                   WaveCliShardServiceShell                    (WaveClientSynchronousConnection &connection);

        void       briefHelp                                       ();

        ResourceId configureServiceShell                           (const vector<string> &arguments);
        void       configureServiceShellHelp                       (void);

        ResourceId registerServiceInstanceShardingCapabilities     (const vector<string> &arguments);
        void       registerServiceInstanceShardingCapabilitiesHelp (void);

        ResourceId getShardOwnerForResource                        (const vector<string> &arguments);
        void       getShardOwnerForResourceHelp                    (void);

    protected :
    public :
        virtual ~WaveCliShardServiceShell ();

    // Now the data members

    private :
        string m_serviceName;
        string m_serviceInstanceName;

    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLISHARDSERVICESHELL_H
