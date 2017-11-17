/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef INTERFACEWORKER_H
#define INTERFACEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

using namespace WaveNs;

namespace IsleNs
{

class NetworkModelObjectManager;

class InterfaceWorker : public WaveWorker
{
    private :
        WaveManagedObject *createManagedObjectInstance (const string &managedObjectClassName);

    protected :
    public :
                 InterfaceWorker (NetworkModelObjectManager *pNetworkModelObjectManger);
        virtual ~InterfaceWorker ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // INTERFACEWORKER_H
