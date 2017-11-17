/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ISLELOCALMANAGEDOBJECT_H
#define ISLELOCALMANAGEDOBJECT_H

#include "IsleObjectModel/IsleManagedObject.h"
#include "IsleObjectModel/IsleLocalManagedObjectBase.h"

namespace IsleNs
{

class IsleLocalManagedObject : virtual public IsleManagedObject, virtual public IsleLocalManagedObjectBase
{
    private :
    protected :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    public :
                        IsleLocalManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual        ~IsleLocalManagedObject ();

        static  string  getClassName          ();

    // Now the data members

    private :
    protected :
    public:
};

}

#endif // ISLELOCALMANAGEDOBJECT_H
