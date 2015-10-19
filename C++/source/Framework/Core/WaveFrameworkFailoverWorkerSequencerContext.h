/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKFAILOVERWORKERSEQUENCERCONTEXT_H
#define PRISMFRAMEWORKFAILOVERWORKERSEQUENCERCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

class PrismFailoverAgent;

class WaveFrameworkFailoverWorkerSequencerContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                                      WaveFrameworkFailoverWorkerSequencerContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                                      ~WaveFrameworkFailoverWorkerSequencerContext ();

                LocationRole                          getThisLocationRole                          () const;
                void                                  setThisLocationRole                          (const LocationRole &thisLocationRole);
                FrameworkObjectManagerFailoverReason  getFailoverReason                            () const;
                void                                  setFailoverReason                            (const FrameworkObjectManagerFailoverReason &failoverReason = FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED);
                UI32                                  getNumberOfFailedLocations                   () const;
                LocationId                            getFailedLocationAtIndex                     (const UI32 &index) const;
                void                                  addFailedLocationId                          (const LocationId &locationId);

                PrismFailoverAgent                   *getPPrismFailoverAgent                       () const;
                void                                  setPPrismFailoverAgent                       (PrismFailoverAgent *pPrismFailoverAgent);

                void                                  setServiceToBeIgnored                        (const WaveServiceId &serviceToBeIgnored);
                WaveServiceId                        getServiceToBeIgnored                        () const;

    // Now the data members

    private :
        LocationRole                          m_thisLocationRole;
        FrameworkObjectManagerFailoverReason  m_failoverReason;
        vector<LocationId>                    m_failedLocationIds;

        PrismFailoverAgent                   *m_pPrismFailoverAgent;

        WaveServiceId                        m_serviceToBeIgnored;

    protected :
    public :
};

}

#endif // PRISMFRAMEWORKFAILOVERWORKERSEQUENCERCONTEXT_H
