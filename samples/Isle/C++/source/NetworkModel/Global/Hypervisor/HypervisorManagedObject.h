/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HYPERVISORMANAGEDOBJECT_H
#define HYPERVISORMANAGEDOBJECT_H

#include "IsleObjectModel/IsleManagedObject.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Types/IpVxAddress.h"

#include <vector>

using namespace std;
using namespace WaveNs;

namespace IsleNs
{

class NetworkModelObjectManager;

class HypervisorManagedObject : virtual public IsleManagedObject
{
    private :
    protected :
        void setupAttributesForCreate      ();
        void setupAttributesForPersistence ();
        void setupKeys                     ();

    public :
                        HypervisorManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager);
        virtual        ~HypervisorManagedObject ();

        static  string  getClassName ();

        const IpVxAddress      &getIpAddress () const;
              void              setIpAddress (const IpVxAddress &ipAddress);

              vector<ObjectId> &getBridges   ();

        // Now the data members

    private :
        IpVxAddress      m_ipAddress;
        vector<ObjectId> m_bridges;

    protected :

};

}

#endif // HYPERVISORMANAGEDOBJECT_H
