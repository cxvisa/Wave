/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef VIRTUALINTERFACEMANAGEDOBJECT_H
#define VIRTUALINTERFACEMANAGEDOBJECT_H

#include "NetworkModel/Global/Interface/InterfaceManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"

namespace IsleNs
{

class NetworkModelObjectManager;

class VirtualInterfaceManagedObject : virtual public InterfaceManagedObject
{
    private :
    protected :
        void setupAttributesForCreate      ();
        void setupAttributesForPersistence ();

    public :
                        VirtualInterfaceManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager);
        virtual        ~VirtualInterfaceManagedObject ();

        static  string  getClassName                  ();

        // Now the data members

    private :
    protected :
};

}

#endif // VIRTUALINTERFACEMANAGEDOBJECT_H
