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
        void setupKeys                     ();

    protected :
    public :
                 ExternalNonNativeServiceInstanceManagedObject (WaveObjectManager *pWaveObjectManager);
                 ExternalNonNativeServiceInstanceManagedObject (WaveObjectManager *pWaveObjectManager, const string &applicationInstanceName);

        virtual ~ExternalNonNativeServiceInstanceManagedObject ();

        static string getClassName ();

        ObjectId getService () const;
        void     setService (const ObjectId &service);

        vector<ObjectId> getShardingCapabilities () const;
        void             setShardingCapabilities (const vector<ObjectId> shardingCapabilities);

    // Now the Data Members

    private :
        ObjectId         m_service;
        vector<ObjectId> m_shardingCapabilities;

    protected :
    public :
};

}

#endif // EXTERNALNONNATIVESERVICEINSTANCEMANAGEDOBJECT_H
