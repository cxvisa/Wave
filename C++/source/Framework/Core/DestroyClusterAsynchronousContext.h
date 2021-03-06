/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DESTROYCLUSTERASYNCHRONOUSCONTEXT_H
#define DESTROYCLUSTERASYNCHRONOUSCONTEXT_H

#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"

namespace WaveNs
{

class DestroyClusterAsynchronousContext : public WaveAsynchronousContext
{
    private :
    protected :
    public :
                                                      DestroyClusterAsynchronousContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext);
        virtual                                      ~DestroyClusterAsynchronousContext ();

                FrameworkObjectManagerFailoverReason  getReasonForDestroyingCluster     () const;
                void                                  setReasonForDestroyingCluster     (const FrameworkObjectManagerFailoverReason &reasonForDestroyingCluster = FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);

                void                                  setOriginalRequester              (const WaveServiceId &waveServiceId);
                WaveServiceId                        getOriginalRequester              () const;

                void                                  setIsRebootRequired               (const bool &isRebootRequired);
                bool                                  getIsRebootRequired               () const;

                bool                                  getIsPreparingForAddNode          () const;
                void                                  setPreparingForAddNode            (const bool &isPreparingForAddNode);
    // Now the data members

    private :
        FrameworkObjectManagerFailoverReason m_reasonForDestroyingCluster;
        WaveServiceId                       m_originalRequester;
        bool                                 m_isRebootRequired;
        bool                                 m_isPreparingForAddNode;
    protected :
    public :
};

}

#endif // DESTROYCLUSTERASYNCHRONOUSCONTEXT_H
