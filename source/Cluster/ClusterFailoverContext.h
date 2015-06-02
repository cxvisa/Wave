/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERFAILOVERCONTEXT_H
#define CLUSTERFAILOVERCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class PrismCluster;
class NodeManagedObject;
class WaveManagedObject;
class WaveNode;

class ClusterFailoverContext : public PrismSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                                      ClusterFailoverContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const FrameworkObjectManagerFailoverReason &failoverReason, const vector<LocationId> &failedLocationIds);
                                                      ClusterFailoverContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const FrameworkObjectManagerFailoverReason &failoverReason, const vector<LocationId> &failedLocationIds);
        virtual                                      ~ClusterFailoverContext ();

                FrameworkObjectManagerFailoverReason  getFailoverReason      () const;
                vector<LocationId>                   &getFailedLocationIds   ();

                PrismCluster                         *getPPrismCluster       ();
                void                                  setPPrismCluster       (PrismCluster *pPrismCluster);

                vector<WaveManagedObject *>          *getPNodeManagedObjects ();
                void                                  setPNodeManagedObjects (vector<WaveManagedObject *> *pNodeManagedObjects);

                bool                                  getIsPrimaryChanged    () const;
                void                                  setIsPrimaryChanged    (const bool &isPrimaryChanged);

                bool                                  isAFailedLocationId    (const LocationId &locationId);
                bool                                  getIsClusterExists     () const;
                void                                  setIsClusterExists     (const bool &isClusterExists);
                WaveNode                             *getThisWaveNode        () const;
                void                                  setThisWaveNode        (WaveNode *pWaveNode);

    // Now the data members

    private :
        FrameworkObjectManagerFailoverReason  m_failoverReason;
        vector<LocationId>                    m_failedLocationIds;

        PrismCluster                         *m_pPrismCluster;
        vector<WaveManagedObject *>          *m_pNodeManagedObjects;
        bool                                  m_isPrimaryChanged;
        bool                                  m_isClusterExists;
        WaveNode                             *m_pThisWaveNode;

    protected :
    public :
};

}

#endif // CLUSTERFAILOVERCONTEXT_H
