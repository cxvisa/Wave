/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DETACHFROMCLUSTERASYNCHRONOUSCONTEXT_H
#define DETACHFROMCLUSTERASYNCHRONOUSCONTEXT_H

#include "Framework/Utils/PrismAsynchronousContext.h"
#include "FrameworkObjectManagerTypes.h"

namespace WaveNs
{

class DetachFromClusterAsynchronousContext : public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                                      DetachFromClusterAsynchronousContext (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext);
        virtual                                      ~DetachFromClusterAsynchronousContext ();

                FrameworkObjectManagerFailoverReason  getReasonForDetachingFromCluster     () const;
                void                                  setReasonForDetachingFromCluster     (const FrameworkObjectManagerFailoverReason &reasonForDetachingFromCluster = FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

    // Now the data members

    private:
        FrameworkObjectManagerFailoverReason m_reasonForDetachingFromCluster;

    protected :
    public :
};

}

#endif // DETACHFROMCLUSTERASYNCHRONOUSCONTEXT_H
