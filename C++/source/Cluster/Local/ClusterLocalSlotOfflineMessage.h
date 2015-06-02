 /**************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh			                                   *
 ***************************************************************************/

#ifndef CLUSTERLOCALSLOTOFFLINEMESSAGE_H
#define CLUSTERLOCALSLOTOFFLINEMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"

using namespace WaveNs;

namespace WaveNs
{

class ClusterLocalSlotOfflineMessage : public PrismMessage
{
    private :
        			void 	setupAttributesForSerialization ();

    protected :
    public :
                    ClusterLocalSlotOfflineMessage ();
                    ClusterLocalSlotOfflineMessage (const UI32 &slotNumber, const UI32 &hwType, const UI32 &slotState);
    virtual        ~ClusterLocalSlotOfflineMessage ();

					 UI32	 getSlotNumber			() const;
					 void	 setSlotNumber		    (const UI32 &slotNumber);
					 UI32    getHwType					() const;
					 void	 setHwType					(const UI32 &hwType);
					 UI32	 getSlotState				 () const;
					 void	 setSlotState				 (const UI32 &slotState);
					
					 // Now the data members
					
	private :
						 UI32	 m_slotNumber;
						 UI32    m_hwType;
						 UI32	 m_slotState;	 

    protected :
    public :
};

}

#endif // CLUSTERLOCALSLOTOFFLINEMESSAGE_H


