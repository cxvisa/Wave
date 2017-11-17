/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ISLEMANAGEDOBJECT_H
#define ISLEMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"

using namespace WaveNs;

namespace IsleNs
{

class IsleManagedObject : virtual public WaveManagedObject
{
    private :
    protected :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    public :
                        IsleManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual        ~IsleManagedObject ();

        static  string  getClassName      ();

    // Now the data members

    private :
    protected :
    public:
};

}

#endif // ISLEMANAGEDOBJECT_H
