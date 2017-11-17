/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef KVMHYPERVISORMANAGEDOBJECT_H
#define KVMHYPERVISORMANAGEDOBJECT_H

#include "NetworkModel/Global/Hypervisor/HypervisorManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"

namespace IsleNs
{

class NetworkModelObjectManager;

class KvmHypervisorManagedObject : virtual public HypervisorManagedObject
{
    private :
        void setupAttributesForCreate      ();
        void setupAttributesForPersistence ();

    protected :
    public :
                        KvmHypervisorManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager);
        virtual        ~KvmHypervisorManagedObject ();

        static  string  getClassName               ();

        // Now the data members

    private :
    protected :
};

}

#endif // KVMHYPERVISORMANAGEDOBJECT_H
