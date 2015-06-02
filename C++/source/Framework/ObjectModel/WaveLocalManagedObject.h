/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVELOCALMANAGEDOBJECT_H
#define WAVELOCALMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveLocalManagedObjectBase.h"

namespace WaveNs
{

class WaveLocalManagedObject : virtual public WaveManagedObject, virtual public WaveLocalManagedObjectBase
{
    private :
    protected :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();

    public :
                       WaveLocalManagedObject (WaveObjectManager *pWaveObjectManager);
        virtual       ~WaveLocalManagedObject ();

        static string  getClassName           ();
		void addWaveSlotLMOObjectId (const ObjectId &waveSlotObjectId);
		vector<ObjectId> getWaveSlotLMOObjectIds ();
		ResourceId removeWaveSlotLMOObjectId (const ObjectId &waveSlotObjectId);

    // Now the data members

    private :
    	vector<ObjectId> m_waveSlotLMOObjectIds;
    protected:
    public :
};

}

#endif // WAVELOCALMANAGEDOBJECT_H
