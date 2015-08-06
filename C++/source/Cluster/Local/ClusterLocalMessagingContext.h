
/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh                                             *
 ***************************************************************************/

#ifndef CLUSTERLOCALMESSAGINGCONTEXT_H
#define CLUSTERLOCALMESSAGINGCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Cluster/Local/WaveSlotLocalManagedObject.h"
#include "Cluster/Local/WaveNode.h"

namespace WaveNs
{

class ClusterLocalMessagingContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                    ClusterLocalMessagingContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                   ~ClusterLocalMessagingContext ();
								   
  	   WaveSlotLocalManagedObject *getWaveSlotManagedObjectPointer ();
	   void						   setWaveSlotManagedObjectPointer (WaveSlotLocalManagedObject *pWaveSlotLocalManagedObject);
	   UI32 					   getSlotNumber ();
	   void						   setSlotNumber (UI32 &slotNumber);
	   UI32 					   getHwType ();
	   void						   setHwType (UI32 &slotNumber);
	   LocationId				   getLocationId ();
	   void						   setLocationId (LocationId &locationId);
	   bool						   getSlotCreatedFlag ();
	   void						   setSlotCreatedFlag (bool slotCreatedFlag);
	   WaveNode					   *getWaveNodePointer ();
	   void						   setWaveNodePointer (WaveNode *pWaveNode);
	   

    // Now the data members

    private :
    	
		WaveSlotLocalManagedObject *m_WaveSlotLocalManagedObjectPointer;
		WaveNode				   *m_waveNodePointer;
		UI32 						m_slotNumber;
		UI32 						m_hwType;
		LocationId 					m_locationId;
		bool						m_slotCreatedFlag;

    protected :
    public :
};

}

#endif // CLUSTERLOCALMESSAGINGCONTEXT_H
