/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TENANTMANAGEDOBJECT_H
#define TENANTMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class TenantManagedObject : public WaveManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    protected :
    public :
                        TenantManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual        ~TenantManagedObject ();

        static  string  getClassName        ();

                UI32    getId               () const;
                void    setId               (const UI32 &id);

    // Now the data members

    private :
        UI32 m_id;

    protected :
    public :
};

}

#endif // TENANTMANAGED_OBJECT_H
