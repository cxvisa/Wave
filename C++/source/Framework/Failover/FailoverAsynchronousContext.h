/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FAILOVERASYNCHRONOUSCONTEXT_H
#define FAILOVERASYNCHRONOUSCONTEXT_H

#include "Framework/Utils/WaveAsynchronousContext.h"

namespace WaveNs
{

class FailoverAsynchronousContext : public WaveAsynchronousContext
{
    private :
    protected :
    public :
                        FailoverAsynchronousContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext, FrameworkObjectManagerFailoverReason failoverReason, vector<LocationId> &failedLocationIds, bool isPrincipalChangedWithThisFailover);
        virtual        ~FailoverAsynchronousContext ();

        FrameworkObjectManagerFailoverReason    getfailoverReason                       () const;
        vector<LocationId>                      getfailedLocationIds                    () const;
        bool                                    getIsPrincipalChangedWithThisFailover   () const;

    // Now the data members

    private:
        FrameworkObjectManagerFailoverReason    m_failoverReason;
        vector<LocationId>                      m_failedLocationIds;
        bool                                    m_isPrincipalChangedWithThisFailover; 

    protected :
    public :
};

}

#endif // FAILOVERASYNCHRONOUSCONTEXT_H
