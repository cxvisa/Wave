/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef OVSBRIDGEMANAGEDOBJECT_H
#define OVSBRIDGEMANAGEDOBJECT_H

#include "IsleObjectModel/IsleManagedObject.h"
#include "NetworkModel/Global/Bridge/BridgeManagedObject.h"

namespace IsleNs
{

class NetworkModelObjectManager;

class OvsBridgeManagedObject : virtual public BridgeManagedObject
{
    private :
        void setupAttributesForCreate      ();
        void setupAttributesForPersistence ();

    protected :
    public :
                        OvsBridgeManagedObject (NetworkModelObjectManager *pNetworkModelObjectManager);
        virtual        ~OvsBridgeManagedObject ();

        static  string  getClassName               ();

        // Now the data members

    private :
    protected :
};

}

#endif // OVSBRIDGEMANAGEDOBJECT_H
