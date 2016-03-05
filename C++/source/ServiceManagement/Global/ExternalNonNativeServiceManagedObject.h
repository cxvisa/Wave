/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef EXTERNALNONNATIVESERVICEMANAGEDOBJECT_H
#define EXTERNALNONNATIVESERVICEMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class ExternalNonNativeServiceManagedObject : public WaveManagedObject
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    protected :
    public :
                 ExternalNonNativeServiceManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual ~ExternalNonNativeServiceManagedObject ();

        static string getClassName ();

        vector<ObjectId> getServiceInstances () const;
        void             addToServiceInstances (const ObjectId &serviceInstance);
        void             deleteFromServiceInstances (const ObjectId &serviceInstance);
        void             setServiceInstances (const vector<ObjectId> &serviceInstances);

    // Now the Data Members

    private :
        vector<ObjectId> m_serviceInstances;

    protected :
    public :
};

}

#endif // EXTERNALNONNATIVESERVICEMANAGEDOBJECT_H
