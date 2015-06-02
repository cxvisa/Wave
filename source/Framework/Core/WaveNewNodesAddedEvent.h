/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#ifndef WAVENEWNODESADDEDEVENT_H
#define WAVENEWNODESADDEDEVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class WaveNewNodesAddedEvent : public PrismEvent
{
    private :

    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 WaveNewNodesAddedEvent ();
        virtual ~WaveNewNodesAddedEvent ();

                void        addNewNodeDetails           (const LocationId &locationId, const string &ipAddress, const UI32 &port);
                UI32        getNumberOfNewLocations     () const;
                LocationId  getLocationIdAtIndex        (const UI32 &index) const;
                string      getIpAddressAtIndex         (const UI32 &index) const;
                UI32        getPortAtIndex              (const UI32 &index) const;

    // Now the data members

    private :

        vector<LocationId> m_locationIdsForNewNodes;
        vector<string>     m_IpAddressesForNewNodes;
        vector<UI32>       m_portsForNewNodes;

    protected :
    public :
};

}

#endif // WAVENEWNODESADDEDEVENT_H
