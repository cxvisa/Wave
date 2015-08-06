/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DESTROYCLUSTERCONTEXT_H
#define DESTROYCLUSTERCONTEXT_H

#include "Framework/Core/DeleteNodesFromClusterContext.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"

namespace WaveNs
{

class DestroyClusterContext : public DeleteNodesFromClusterContext
{
    private :
    protected :
    public :
                                                      DestroyClusterContext            (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                                      DestroyClusterContext            (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                                      ~DestroyClusterContext            ();

                LocationRole                          getThisLocationRoleBeforeDestroy () const;
                void                                  setThisLocationRoleBeforeDestroy (const LocationRole &thisLocationRoleBeforeDestroy);
                FrameworkObjectManagerFailoverReason  getReasonForDestroyingCluster    () const;
                void                                  setReasonForDestroyingCluster    (const FrameworkObjectManagerFailoverReason &reasonForDestroyingCluster = FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
                void                                  setIsRebootRequired              (const bool &isRebootRequired);
                bool                                  getIsRebootRequired              () const;

    // Now the data members

    private :
        LocationRole                         m_thisLocationRoleBeforeDestroy;
        FrameworkObjectManagerFailoverReason m_reasonForDestroyingCluster;
        bool                                 m_isRebootRequired;

    protected :
    public :
};

}

#endif // DESTROYCLUSTERCONTEXT_H
