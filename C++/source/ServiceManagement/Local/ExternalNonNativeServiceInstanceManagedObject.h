/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef EXTERNALNONNATIVESERVICEINSTANCEMANAGEDOBJECT_H
#define EXTERNALNONNATIVESERVICEINSTANCEMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveLocalManagedObject.h"

namespace WaveNs
{

class ExternalNonNativeServiceInstanceManagedObject : public WaveLocalManagedObject
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    protected :
    public :
                 ExternalNonNativeServiceInstanceManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual ~ExternalNonNativeServiceInstanceManagedObject ();

        static string getClassName ();

        ObjectId getService () const;
        void     setService (const ObjectId &service);

    // Now the Data Members

    private :
        ObjectId m_service;

    protected :
    public :
};

}

#endif // EXTERNALNONNATIVESERVICEINSTANCEMANAGEDOBJECT_H
