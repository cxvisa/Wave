/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef BRIDGEWORKER_H
#define BRIDGEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

using namespace WaveNs;

namespace IsleNs
{

class NetworkModelObjectManager;

class BridgeWorker : public WaveWorker
{
    private :
        WaveManagedObject *createManagedObjectInstance (const string &managedObjectClassName);

    protected :
    public :
                 BridgeWorker (NetworkModelObjectManager *pNetworkModelObjectManger);
        virtual ~BridgeWorker ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // BRIDGEWORKER_H
