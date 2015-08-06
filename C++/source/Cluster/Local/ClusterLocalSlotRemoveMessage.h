 /**************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jitendra Singh			                                   *
 ***************************************************************************/

#ifndef CLUSTERLOCALSLOTREMOVEMESSAGE_H
#define CLUSTERLOCALSLOTREMOVEMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"

using namespace WaveNs;

namespace WaveNs
{

class ClusterLocalSlotRemoveMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                    ClusterLocalSlotRemoveMessage ();
					ClusterLocalSlotRemoveMessage (const UI32 &slotNumber);
                    ClusterLocalSlotRemoveMessage (const UI32 &slotNumber, const UI32 &hwType);
                    ClusterLocalSlotRemoveMessage (const UI32 &slotNumber, const UI32 &hwType, const LocationId &locationId);
    virtual        ~ClusterLocalSlotRemoveMessage ();
					UI32 getSlotNumber ();
					void setSlotNumber (const UI32 &slotNumber);
					UI32 getHwType ();
					void setHwType (const UI32 &hwType);
					LocationId getLocationId ();
					void setLocationId (const LocationId &locationId);
	private:


    // Now the data members


    private :
		UI32 m_slotNumber;
		UI32 m_hwType;
		LocationId m_locationId;

    protected :
    public :
};

}

#endif // CLUSTERLOCALSLOTREMOVEMESSAGE_H


