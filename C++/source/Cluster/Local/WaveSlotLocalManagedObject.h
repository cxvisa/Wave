/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh                                               *
 ***************************************************************************/

#ifndef WAVESLOTLOCALMANAGEDOBJECT_H
#define WAVESLOTLOCALMANAGEDOBJECT_H

#include "Cluster/Local/WaveSlotLocalManagedObjectBase.h"
#include "Framework/ObjectModel/WaveLocalManagedObject.h"

namespace WaveNs
{
class ClusterLocalObjectManager;

class WaveSlotLocalManagedObject : virtual public WaveLocalManagedObject, virtual public WaveSlotLocalManagedObjectBase
{
    private :
        WaveSlotLocalManagedObject ();

    protected :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    public :
        WaveSlotLocalManagedObject (ClusterLocalObjectManager *pClusterLocalObjectManager);
		WaveSlotLocalManagedObject (ClusterLocalObjectManager *pClusterLocalObjectManager, UI32 &slotNumber, UI32 &objectType, UI32 &hwType, UI32 &hwId, UI32 &slotState, UI32 &reason, UI32 &version);
		
        virtual        ~WaveSlotLocalManagedObject ();

        static  string  getClassName        ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESLOTLOCALMANAGEDOBJECT_H
