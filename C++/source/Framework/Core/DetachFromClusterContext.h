/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DETACHFROMCLUSTERCONTEXT_H
#define DETACHFROMCLUSTERCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"

namespace WaveNs
{

class DetachFromClusterContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                                                      DetachFromClusterContext         (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                                      DetachFromClusterContext         (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                                      ~DetachFromClusterContext         ();

                LocationRole                          getThisLocationRoleBeforeDetach  () const;
                void                                  setThisLocationRoleBeforeDetach  (const LocationRole &thisLocationRoleBeforeDetach);
                FrameworkObjectManagerFailoverReason  getReasonForDetachingFromCluster () const;
                void                                  setReasonForDetachingFromCluster (const FrameworkObjectManagerFailoverReason &reasonForDetachingFromCluster = FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

    // Now the data members

    private :
        LocationRole                         m_thisLocationRoleBeforeDetach;
        FrameworkObjectManagerFailoverReason m_reasonForDetachingFromCluster;

    protected :
    public :
};

}

#endif // DETACHFROMCLUSTERCONTEXT_H
