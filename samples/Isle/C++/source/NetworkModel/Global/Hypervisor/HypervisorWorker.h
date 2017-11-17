/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HYPERVISORWORKER_H
#define HYPERVISORWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

using namespace WaveNs;

namespace IsleNs
{

class NetworkModelObjectManager;

class HypervisorWorker : public WaveWorker
{
    private :
        WaveManagedObject *createManagedObjectInstance (const string &managedObjectClassName);

    protected :
    public :
                 HypervisorWorker (NetworkModelObjectManager *pNetworkModelObjectManger);
        virtual ~HypervisorWorker ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // HYPERVISORWORKER_H
