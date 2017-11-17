/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef INTERFACEMANAGEDOBJECT_H
#define INTERFACEMANAGEDOBJECT_H

#include "IsleObjectModel/IsleManagedObject.h"
#include "Framework/Types/MacAddress.h"

namespace IsleNs
{

class NetworkModelObjectManager;

class InterfaceManagedObject : virtual public IsleManagedObject
{
    private :
    protected :
        void setupAttributesForCreate      ();
        void setupAttributesForPersistence ();

    public :
                        InterfaceManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager);
        virtual        ~InterfaceManagedObject ();

        static  string  getClassName ();

        const MacAddress &getMacAddress () const;
              void        setMacAddress (const MacAddress &macAddress);

        // Now the data members

    private :
        MacAddress m_macAddress;

    protected :
    public :

};

}

#endif // INTERFACEMANAGEDOBJECT_H
