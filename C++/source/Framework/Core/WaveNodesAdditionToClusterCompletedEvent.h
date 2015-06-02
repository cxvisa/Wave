/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Sudhakar Jha                                              *
 ***************************************************************************/

#ifndef WAVENODESADDITIONTOCLUSTERCOMPLETEDEVENT_H
#define WAVENODESADDITIONTOCLUSTERCOMPLETEDEVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class WaveNodesAdditionToClusterCompletedEvent : public PrismEvent
{
    private :

    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 WaveNodesAdditionToClusterCompletedEvent ();
        virtual ~WaveNodesAdditionToClusterCompletedEvent ();

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

#endif // WAVENODESADDITIONTOCLUSTERCOMPLETEDEVENT_H

