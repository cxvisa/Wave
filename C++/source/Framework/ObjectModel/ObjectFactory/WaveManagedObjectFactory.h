/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMMANAGEDOBJECTFACTORY_H
#define PRISMMANAGEDOBJECTFACTORY_H

#include "Framework/Types/Types.h"

#include <string>

using namespace std;

namespace WaveNs
{

class WaveManagedObject;
class WaveObjectManager;

class WaveManagedObjectFactory
{
    private :
    protected :
    public :
        static WaveManagedObject *getWaveManagedObjectInstance         (const PrismServiceId &prismServiceId, const  string &className);
        static WaveObjectManager *getWaveObjectManagerForManagedObject (const PrismServiceId &prismServiceId, const  string &className);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMMANAGEDOBJECTFACTORY_H
