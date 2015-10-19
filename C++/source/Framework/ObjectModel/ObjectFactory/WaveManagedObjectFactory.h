/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTFACTORY_H
#define WAVEMANAGEDOBJECTFACTORY_H

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
        static WaveManagedObject *getWaveManagedObjectInstance         (const WaveServiceId &waveServiceId, const  string &className);
        static WaveObjectManager *getWaveObjectManagerForManagedObject (const WaveServiceId &waveServiceId, const  string &className);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTFACTORY_H
