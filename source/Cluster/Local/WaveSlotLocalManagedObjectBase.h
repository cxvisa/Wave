/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef WAVESLOTLOCALMANAGEDOBJECTBASE_H
#define WAVESLOTLOCALMANAGEDOBJECTBASE_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveManagedObject;

class WaveSlotLocalManagedObjectBase 
{
    private :
        WaveSlotLocalManagedObjectBase ();

    protected :
        void setupAttributesForPersistence  ();
        void setupAttributesForCreate       ();

    public :
        WaveSlotLocalManagedObjectBase (WaveManagedObject *pWaveManagedObject);
		WaveSlotLocalManagedObjectBase (WaveManagedObject *pWaveManagedObject, UI32 &slotNumber, UI32 &objectType, UI32 &hwType, UI32 &hwId, UI32 &slotState, UI32 &reason, UI32 &version);
		
        virtual        ~WaveSlotLocalManagedObjectBase ();

        static  string  getClassName        ();
		UI32 	getSlotNumber ();
		void	setSlotNumber (const UI32 &slotNumber);
		UI32    getObjectType ();
		void    setObjectType (const UI32 &objectType);
		UI32    getReason ();
		void    setReason (const UI32 &reason);
		UI32    getHwType ();
		void    setHwType (const UI32 &hwType);
		UI32    getHwId   ();
		void    setHwId   (const UI32 &hwId);
		UI32    getVersion ();
		void    setVersion (const UI32 &version);
		UI32 	getSlotState ();
		void 	setSlotState (const UI32 &slotState);
    // Now the data members

    private :

        WaveManagedObject *m_pWaveManagedObject;
        UI32    m_slotNumber;
		UI32 	m_objectType; // blade function type
		UI32 	m_hwType; 	// blade type
		UI32 	m_hwId; 
		UI32	m_slotState; 
		UI32 	m_reason; 
		UI32 	m_version; 
		
    protected :
    public :
};

}

#endif // WAVESLOTLOCALMANAGEDOBJECTBASE_H
