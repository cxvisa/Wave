 /**************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou     			                                   *
 ***************************************************************************/

#ifndef CLUSTERLOCALSLOTREMOVEALLMESSAGE_H
#define CLUSTERLOCALSLOTREMOVEALLMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "Cluster/Local/ClusterLocalTypes.h"

using namespace WaveNs;

namespace WaveNs
{

class ClusterLocalSlotRemoveAllMessage : public PrismMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                    ClusterLocalSlotRemoveAllMessage ();
                    ClusterLocalSlotRemoveAllMessage (const LocationId &locationId);
                    ClusterLocalSlotRemoveAllMessage (const LocationId &locationId, const UI32 &hwType);
    virtual        ~ClusterLocalSlotRemoveAllMessage ();
					LocationId getLocationId ();
					void setLocationId (const LocationId &locationId);
                    UI32 getHwType ();
                    void setHwType (const UI32 &hwType);

	private:


    // Now the data members


    private :
		LocationId m_locationId;
        UI32 m_hwType;

    protected :
    public :
};

}

#endif // CLUSTERLOCALSLOTREMOVEALLMESSAGE_H


