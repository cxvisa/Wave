/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef LOCKMANAGEDOBJECT_H
#define LOCKMANAGEDOBJECT_H

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Types/DateTime.h"

#include <vector>

using namespace WaveNs;

namespace WaveNs
{

class LockManagedObject : public WaveManagedObject
{
    private :
        virtual void             setupAttributesForPersistence ();
        virtual void             setupAttributesForCreate      ();

    protected :
    public :
                                 LockManagedObject   (WaveObjectManager *pWaveObjectManager);
                                 LockManagedObject   (WaveObjectManager *pWaveObjectManager, const LocationId &locationId, const string &serviceString, const WaveServiceId &serviceId);
        virtual                 ~LockManagedObject   ();

        static string            getClassName               ();

               LocationId        getLocationId              () const;
        const  string&           getServiceString           () const;
               WaveServiceId    getServiceId               () const;
               

               void              setLocationId              (const LocationId locationId);
               void              setServiceString           (const string &serviceString);
               void              setServiceId               (const WaveServiceId serviceId);

               void              resetLockManagedObject     ();
               
            LockManagedObject   &operator=                  (const LockManagedObject &lockManagedObject);             

    // Now the data members

    private :
               LocationId        m_locationId;
               string            m_serviceString;
               WaveServiceId    m_serviceId;

    protected :
    public :
};

}

#endif //LOCKMANAGEDOBJECT_H
