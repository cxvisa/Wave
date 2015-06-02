/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMCLUSTER_H
#define PRISMCLUSTER_H

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

#include <vector>

using namespace WaveNs;

namespace WaveNs
{

class PrismCluster : public WaveManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    protected :
    public :
                                 PrismCluster           (WaveObjectManager *pWaveObjectManager);
        virtual                 ~PrismCluster           ();

        static string            getClassName           ();

               LocationId        getPrimaryLocationId   () const;
               void              setPrimaryLocationId   (const LocationId &primaryLocationId);
               string            getPrimaryIpAddress    () const;
               void              setPrimaryIpAddress    (const string &primaryIpAddress);
               UI32              getPrimaryPort         () const;
               void              setPrimaryPort         (const UI32 &port);
               void              removeAllSecondryNodes ();
               bool              isAKnownSecondaryNode  (const ObjectId &secondaryNodeObjectId);
               void              addSecondaryNode       (const ObjectId &secondaryNodeObjectId);
               void              removeSecondaryNode    (const ObjectId &secondaryNodeObjectId);
               void              setSecondaryNodes      (vector<ObjectId> &secondaryNodes);
               vector<ObjectId>  getSecondaryNodes      () const;

    // Now the data members

    private :
        LocationId       m_primaryLocationId;
        string           m_primaryIpAddress;
        UI32             m_primaryPort;
        vector<ObjectId> m_secondaryNodes;

    protected :
    public :
};

}

#endif // PRISMCLUSTER_H
