/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ISLELOCALMANAGEDOBJECTBASE_H
#define ISLELOCALMANAGEDOBJECTBASE_H

#include "Framework/ObjectModel/WaveLocalManagedObjectBase.h"

using namespace WaveNs;

namespace IsleNs
{

class IsleManagedObject;

class IsleLocalManagedObjectBase : virtual public WaveLocalManagedObjectBase
{
    private :
    protected :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    public :
                           IsleLocalManagedObjectBase (IsleManagedObject *pIsleManagedObject);
        virtual           ~IsleLocalManagedObjectBase ();

        static string      getClassName               ();

    // Now the data members

    private :
    protected:
    public :
};

}

#endif // ISLELOCALMANAGEDOBJECTBASE_H
