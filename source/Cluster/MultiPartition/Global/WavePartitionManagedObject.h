/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jay Iyer                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef WAVEPARTITIONMANAGEDOBJECT_H
#define WAVEPARTITIONMANAGEDOBJECT_H

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class WavePartitionManagedObject  : public WaveManagedObject 
{
    private :
    protected :
        void setupAttributesForPersistence  ();
        void setupAttributesForCreate       ();

    public :
                           WavePartitionManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual           ~WavePartitionManagedObject ();

        static  string      getClassName                ();

                bool        isWaveNodeMappedToPartition(ObjectId &objId);
                void        addWaveNodeToPartition(ObjectId &objId);
                UI32        removeWaveNodeFromPartition(ObjectId &objId);

                void        setPartitionName(const string &name);
                string      getPartitionName(void);

    // Now the data members
    private :
        vector<ObjectId>                m_waveNodeObjectIdList; 
        string                          m_partitionName; 

    protected:
    public :
};

}

#endif // WAVEPARTITIONMANAGEDOBJECT_H
