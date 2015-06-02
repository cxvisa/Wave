/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LOCATION_H
#define LOCATION_H

#include <map>
#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/Utils/ClientStreamingSocket.h"

using namespace std;

namespace WaveNs
{

class SubLocation;

class Location : public LocationBase
{
    private :
        virtual void getKnownRemoteLocations (vector<LocationId> &remoteLocationsVector);
        virtual void getKnownLocations       (vector<LocationId> &knownLocationsVector);
        virtual void getConnectedLocations   (vector<LocationId> &connectedLocationsVector);
        virtual void getKnownSubLocations    (vector<LocationId> &knownSubLocationsVector);

    protected :
    public :
                                       Location                                         (LocationId locationId, string &ipAddress, SI32 port);
        virtual                       ~Location                                         ();
        virtual bool                   supportsSubLocations                             ();
        virtual void                   addSubLocation                                   (LocationId locationId, string &ipAddress, SI32 port);
        virtual void                   addKnownLocation                                 (LocationId knownLocationId, string &ipAddress, SI32 port);
        virtual void                   removeKnownLocation                              (LocationId knownLocationId);
        virtual void                   initializeClientCommunications                   ();
        virtual ClientStreamingSocket *getClientStreamingSocketForRemoteLocation        (LocationId locationId);
        virtual ClientStreamingSocket *getClientStreamingSocketForHaPeer                ();
        virtual void                   invalidateClientStreamingSocketForRemoteLocation (LocationId locationId);
        virtual void                   invalidateClientStreamingSocketForHaPeer         ();
        virtual ResourceId             connectToRemoteLocation                          (LocationId locationId, UI32 numberOfRetries = 0, UI32 maximumNumberOfSecondsToTryFor = 0);
        virtual ResourceId             connectToHaPeer                                  (const string &ipAddress, const SI32 port, UI32 numberOfRetries, UI32 maximumNumberOfSecondsToTryFor);
        virtual LocationId             getLocationIdForIpAddressAndPort                 (const string &ipAddress, const SI32 &port);
        virtual string                 getIpAddressForLocationId                        (const LocationId &locationId);
        virtual SI32                   getPortForLocationId                             (const LocationId &locationId);
        virtual bool                   isAKnownLocation                                 (const LocationId &locationId);
        virtual bool                   isAConnectedLocation                             (const LocationId &locationId);
        virtual void                   resetLocationToStandAlone                        (const LocationId &locationId);
        virtual void                   resetLocationToPrimary                           ();
        virtual void                   getFullyConnectedLocations                       (vector<LocationId> &connectedLocationsVector);
        virtual void                   removeAllKnownLocations                          ();
                void                   removeAllSubLocations                            ();

    // Now the data members

    private :
        // Datastructures to hold the sub locations

        map<LocationId, SubLocation *>           m_subLocations;
        map<LocationId, ClientStreamingSocket *> m_clientSocketsForSubLocations;

        // Datastructures to hold the other kown locations.

        map<LocationId, Location*>               m_knownLocations;
        map<LocationId, ClientStreamingSocket *> m_clientSocketsForKnownLocations;

        ClientStreamingSocket *                  m_clientSocketForHaPeer;

    protected :
    public :
};

}

#endif // LOCATION_H
