/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef BRIDGEMANAGEDOBJECT_H
#define BRIDGEMANAGEDOBJECT_H

#include "IsleObjectModel/IsleManagedObject.h"
#include "Framework/ObjectModel/ObjectId.h"

#include <vector>


using namespace std;
using namespace WaveNs;

namespace IsleNs
{

class NetworkModelObjectManager;

class BridgeManagedObject : virtual public IsleManagedObject
{
    private :
    protected :
        void setupAttributesForCreate      ();
        void setupAttributesForPersistence ();

    public :
                        BridgeManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager);
        virtual        ~BridgeManagedObject ();

        static  string  getClassName ();

        static ObjectId getObjectIdById (const string &id);

        const string &getId () const;
              void    setId (const string &id);

        vector<ObjectId> &getTapInterfaces ();

        const ObjectId &getHypervisor () const;
              void      setHypervisor (const ObjectId &hypervisor);


        // Now the data members

    private :
        string           m_id;
        vector<ObjectId> m_tapInterfaces;
        ObjectId         m_hypervisor;

    protected :
    public :

};

}

#endif // BRIDGEMANAGEDOBJECT_H
