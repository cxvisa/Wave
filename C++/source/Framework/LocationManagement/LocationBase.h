/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LOCATIONBASE_H
#define LOCATIONBASE_H

#include <string>
#include <vector>
#include <set>
#include <Framework/Types/Types.h>
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/Utils/ClientStreamingSocket.h"
#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Utils/WaveMutex.h"

using namespace std;

namespace WaveNs
{

class WaveMessage;
class InterLocationMulticastMessage;

class LocationBase
{
    private :
        virtual void getKnownRemoteLocations (vector<LocationId> &remoteLocationsVector)    = 0;
        virtual void getKnownLocations       (vector<LocationId> &knownLocationsVector)     = 0;
        virtual void getConnectedLocations   (vector<LocationId> &connectedLocationsVector) = 0;
        virtual void getKnownSubLocations    (vector<LocationId> &knownSubLocationsVector)  = 0;

    protected :
             LocationBase                  (UI32 locationId, string &ipAddress, SI32 port);
        void lockAccess                    ();
        void unlockAccess                  ();
        void setLocationId                 (LocationId locationId);
        void lockConnectionEstablishment   ();
        void unlockConnectionEstablishment ();

    public :
        virtual                                   ~LocationBase                                     ();
        virtual       bool                         supportsSubLocations                             () = 0;
        virtual       void                         addSubLocation                                   (LocationId locationId, string &ipAddress, SI32 port) = 0;
                      ServerStreamingSocketStatus  initializeServerCommunications                   ();
        virtual       void                         initializeClientCommunications                   () = 0;
                      ServerStreamingSocketStatus  initializeHaPeerServerCommunications             ();
        virtual       ClientStreamingSocket       *getClientStreamingSocketForRemoteLocation        (LocationId locationId) = 0;
        virtual       ClientStreamingSocket       *getClientStreamingSocketForHaPeer                () = 0;
        virtual       void                         invalidateClientStreamingSocketForRemoteLocation (LocationId locationId) = 0;
        virtual       void                         invalidateClientStreamingSocketForHaPeer         ();

        virtual       ResourceId                   connectToRemoteLocation                          (LocationId locationId, UI32 numberOfRetries = 0, UI32 maximumNumberOfSecondsToTryFor = 0) = 0;
        virtual       ResourceId                   connectToHaPeer                                  (const string &ipAddress, const SI32 port, UI32 numberOfRetries, UI32 maximumNumberOfSecondsToTryFor);
        virtual       void                         addKnownLocation                                 (LocationId knownLocationId, string &ipAddress, SI32 port) = 0;
        virtual       void                         removeKnownLocation                              (LocationId knownLocationId) = 0;
                      ResourceId                   postToRemoteLocation                             (const string &bufferToPost, LocationId locationId);
                      ResourceId                   postToRemoteLocation                             (InterLocationMulticastMessage *pInterLocationMulticastMessage, set<LocationId> locationsToSent);
                      ResourceId                   postToRemoteLocation                             (WaveMessage *pWaveMessage, LocationId locationId);
                      ResourceId                   postToHaPeerLocation                             (const string &bufferToPost);
                      ResourceId                   postToHaPeerLocation                             (WaveMessage *pWaveMessage);
                      bool                         acceptNewConnection                              (ServerStreamingSocket &newSocket);
                      bool                         acceptHaPeerConnection                           (ServerStreamingSocket &newSocket);
                const string                      &getIpAddress                                     () const;
                const string                      &getIpAddressForHaInterface                       () const;
                      void                         resetIpAddress                                   (const string &newIpAddress);
                      void                         resetIpAddressForHaInterface                     (const string &newIpAddress);
                const SI32                        &getPort                                          () const;
                const SI32                        &getHaPeerPort                                    () const;
                const LocationRole                &getRole                                          () const;
                const UI32                        &getLocationId                                    () const;
        virtual       LocationId                   getLocationIdForIpAddressAndPort                 (const string &ipAddress, const SI32 &port) = 0;
        virtual       string                       getIpAddressForLocationId                        (const LocationId &locationId) = 0;
        virtual       SI32                         getPortForLocationId                             (const LocationId &locationId) = 0;

        static  const UI32                         getSubLocationMask                               ();
        static        bool                         isASubLocation                                   (LocationId locationId);
                      bool                         isASubLocation                                   ();
        virtual       bool                         isAKnownLocation                                 (const LocationId &locationId) = 0;
        virtual       bool                         isAConnectedLocation                             (const LocationId &locationId) = 0;

                      void                         setClusterPrimaryLocationId                      (const LocationId &locationId);
                const LocationId                   getClusterPrimaryLocationId                      ();
                      void                         setClusterPrimaryPort                            (const SI32 &port);
                const SI32                         getClusterPrimaryPort                            ();

                      void                         setLocationRole                                  (const LocationRole &locationRole);
                const LocationRole                 getLocationRole                                  ();

        virtual       void                         resetLocationToStandAlone                        (const LocationId &locationId) = 0;
        virtual       void                         resetLocationToPrimary                           () = 0;
        virtual       void                         getFullyConnectedLocations                       (vector<LocationId> &connectedLocationsVector) ;
        virtual       void                         removeAllKnownLocations                          () = 0;
        virtual       void                         removeAllSubLocations                            () = 0;

    // Now the data members

    private :
        WaveMutex m_accessMutex;
        WaveMutex m_connectionEstablishmentMutex;

    protected :
        LocationRole           m_locationRole;
        LocationId             m_locationId;
        string                 m_ipAddress;
        string                 m_ipAddressForHaInterface;
        SI32                   m_port;
        SI32                   m_portForHaPeer;

        LocationId             m_clusterPrimaryLocationId;
        SI32                   m_clusterPrimaryPort;

        ServerStreamingSocket *m_pServerSocketForLocation;
        ServerStreamingSocket *m_pServerSocketForHaPeer;

    public :

    friend class PrismFrameworkObjectManager;
    friend class PersistentPrismBootAgent;
    friend class PersistentWithDefaultPrismBootAgent;
    friend class PersistentWithDefaultForHABootAgent;
    friend class PrismFrameworkObjectManagerHaSyncWorker;
    friend class PrismFrameworkConfigurationWorker;
};

}

#endif // LOCATIONBASE_H
