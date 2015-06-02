/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SUBLOCATION_H
#define SUBLOCATION_H

#include "Framework/LocationManagement/LocationBase.h"
#include "Framework/Utils/ClientStreamingSocket.h"

namespace WaveNs
{

class Location;

class SubLocation : public LocationBase
{
    private :
        virtual void getKnownRemoteLocations (vector<LocationId> &remoteLocationsVector);
        virtual void getKnownLocations       (vector<LocationId> &knownLocationsVector);
        virtual void getConnectedLocations   (vector<LocationId> &connectedLocationsVector);
        virtual void getKnownSubLocations    (vector<LocationId> &knownSubLocationsVector);

    protected :
    public :
                                       SubLocation                                      (UI32 parentLocationId, string &parentIpAddress, SI32 parentPort, UI32 locationId, string &ipAddress, SI32 port);
        virtual                       ~SubLocation                                      ();
                void                   setPParentLocation                               (Location *pParentLocation);
        virtual bool                   supportsSubLocations                             ();
        virtual void                   addSubLocation                                   (LocationId locationId, string &ipAddress, SI32 port);
        virtual void                   initializeClientCommunications                   ();
        virtual ClientStreamingSocket *getClientStreamingSocketForRemoteLocation        (LocationId locationId);
        virtual ClientStreamingSocket* getClientStreamingSocketForHaPeer                ();
        virtual void                   invalidateClientStreamingSocketForRemoteLocation (LocationId locationId);
        virtual ResourceId             connectToRemoteLocation                          (LocationId locationId, UI32 numberOfRetries = 0, UI32 maximumNumberOfSecondsToTryFor = 0);
        virtual LocationId             getLocationIdForIpAddressAndPort                 (const string &ipAddress, const SI32 &port);
        virtual string                 getIpAddressForLocationId                        (const LocationId &locationId);
        virtual SI32                   getPortForLocationId                             (const LocationId &locationId);
        virtual void                   addKnownLocation                                 (LocationId knownLocationId, string &ipAddress, SI32 port);
        virtual void                   removeKnownLocation                              (LocationId knownLocationId);

                UI32                   getParentLocationId                              () const;
                bool                   isAKnownLocation                                 (const LocationId &locationId);
                bool                   isAConnectedLocation                             (const LocationId &locationId);

        virtual void                   resetLocationToStandAlone                        (const LocationId &locationId);
        virtual void                   resetLocationToPrimary                           ();
        virtual void                   removeAllKnownLocations                          ();
        virtual void                   removeAllSubLocations                            ();

    // Now the data members

    private :
        Location              *m_pParentLocation;
        ClientStreamingSocket *m_pClientSocketForParentLocation;

    protected :
    public :
};

}

#endif // SUBLOCATION_H
