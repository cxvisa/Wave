/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TAPINTERFACEMANAGEDOBJECT_H
#define TAPINTERFACEMANAGEDOBJECT_H

#include "NetworkModel/Global/Interface/VirtualInterfaceManagedObject.h"
#include "IsleObjectModel/IsleManagedObject.h"
#include "Framework/ObjectModel/ObjectId.h"

using namespace WaveNs;

namespace IsleNs
{

class NetworkModelObjectManager;

class TapInterfaceManagedObject : virtual public VirtualInterfaceManagedObject
{
    private :
        virtual void   setupAttributesForCreate                 ();
        virtual void   setupAttributesForPersistence            ();
        virtual string getUserDefinedKeyCombinationValueForJson () const;

    protected :
    public :
                        TapInterfaceManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager);
        virtual        ~TapInterfaceManagedObject ();

        static  string                     getClassName                             ();

        static  TapInterfaceManagedObject *getByBridgeAndId                         (const ObjectId &bridge, const UI32 &id);

        const ObjectId &getBridge           () const;
              void      setBridge           (const ObjectId &bridge);

        const UI32     &getId               () const;
              void      setId               (const UI32 &id);

        const string    getBridgeId         () const;

        // Now the data members

    private :
        ObjectId m_bridge;
        UI32     m_id;

    protected :
    public :
};

}

#endif // TAPINTERFACEMANAGEDOBJECT_H
