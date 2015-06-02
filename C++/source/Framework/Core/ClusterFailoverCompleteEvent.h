/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#ifndef CLUSTERFAILOVERCOMPLETEEVENT_H
#define CLUSTERFAILOVERCOMPLETEEVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class ClusterFailoverCompleteEvent : public PrismEvent
{
    private :
    protected :

    public :
                 ClusterFailoverCompleteEvent (FrameworkObjectManagerFailoverReason failoverReason, vector<LocationId> &failedLocationIds, bool isPrincipalChangedWithThisFailover);
        virtual ~ClusterFailoverCompleteEvent ();


        FrameworkObjectManagerFailoverReason    getfailoverReason                        () const;
        void                                    setFailoverReason                        (FrameworkObjectManagerFailoverReason failoverReason);

        vector<LocationId>                      getFailoverReason                       () const;
        void                                    setFailedLocationIds                    (const vector<LocationId> &failedLocationIds);

        bool                                    getIsPrincipalChangedWithThisFailover   () const;
        void                                    setIsPrincipalChangedWithThisFailover   (bool isPrincipalChangedWithThisFailover);
        

    // Now the data members

    private :
        FrameworkObjectManagerFailoverReason    m_failoverReason;
        vector<LocationId>                      m_failedLocationIds;
        bool                                    m_isPrincipalChangedWithThisFailover;
    protected :
    public :
};

}

#endif // CLUSTERFAILOVERCOMPLETEEVENT_H
