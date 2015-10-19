/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERFAILOVERCONTEXT_H
#define CLUSTERFAILOVERCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveCluster;
class NodeManagedObject;
class WaveManagedObject;
class WaveNode;

class ClusterFailoverContext : public WaveSynchronousLinearSequencerContext
{
    private :
    protected :
    public :
                                                      ClusterFailoverContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const FrameworkObjectManagerFailoverReason &failoverReason, const vector<LocationId> &failedLocationIds);
                                                      ClusterFailoverContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps, const FrameworkObjectManagerFailoverReason &failoverReason, const vector<LocationId> &failedLocationIds);
        virtual                                      ~ClusterFailoverContext ();

                FrameworkObjectManagerFailoverReason  getFailoverReason      () const;
                vector<LocationId>                   &getFailedLocationIds   ();

                WaveCluster                         *getPWaveCluster       ();
                void                                  setPWaveCluster       (WaveCluster *pWaveCluster);

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

        WaveCluster                         *m_pWaveCluster;
        vector<WaveManagedObject *>          *m_pNodeManagedObjects;
        bool                                  m_isPrimaryChanged;
        bool                                  m_isClusterExists;
        WaveNode                             *m_pThisWaveNode;

    protected :
    public :
};

}

#endif // CLUSTERFAILOVERCONTEXT_H
