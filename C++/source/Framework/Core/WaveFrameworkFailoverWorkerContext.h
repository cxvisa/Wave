/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKFAILOVERWORKERCONTEXT_H
#define WAVEFRAMEWORKFAILOVERWORKERCONTEXT_H

#include "Framework/Utils/WaveAsynchronousContext.h"
#include "Framework/Core/FrameworkObjectManagerTypes.h"
#include <vector>

namespace WaveNs
{

class WaveFrameworkFailoverWorkerContext : public WaveAsynchronousContext
{
    private :
    protected :
    public :
                                                      WaveFrameworkFailoverWorkerContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                                      ~WaveFrameworkFailoverWorkerContext ();

                LocationRole                          getThisLocationRole                 () const;
                void                                  setThisLocationRole                 (const LocationRole &thisLocationRole);
                FrameworkObjectManagerFailoverReason  getFailoverReason                   () const;
                void                                  setFailoverReason                   (const FrameworkObjectManagerFailoverReason &failoverReason = FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
                UI32                                  getNumberOfFailedLocations          () const;
                LocationId                            getFailedLocationAtIndex            (const UI32 &index) const;
                void                                  addFailedLocationId                 (const LocationId &locationId);
                void                                  getFailedLocationIds                (vector<LocationId> &failedLocationIds);
                void                                  setServiceToBeIgnored               (const WaveServiceId &serviceToBeIgnored);
                WaveServiceId                        getServiceToBeIgnored               () const;
                bool                                  isSecondaryControlledFailoverDueToPrimaryRemoval () const;
                void                                  setSecondaryControlledFailoverDueToPrimaryRemoval ();
                bool                                  getIsConfigurationChange            () const;
                void                                  setIsConfigurationChange            (const bool isConfigurationChange);

    // Now the data members

    private :
        LocationRole                         m_thisLocationRole;
        FrameworkObjectManagerFailoverReason m_failoverReason;
        vector<LocationId>                   m_failedLocationIds;
        WaveServiceId                       m_serviceToBeIgnored;
        bool                                 m_secondaryControlledFailoverDueToPrimaryRemoval;
        bool                                 m_isConfigurationChange;
    protected :
    public :
};

}

#endif // WAVEFRAMEWORKFAILOVERWORKERCONTEXT_H
