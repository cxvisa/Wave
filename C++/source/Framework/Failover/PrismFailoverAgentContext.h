/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMFAILOVERAGENTCONTEXT_H
#define PRISMFAILOVERAGENTCONTEXT_H

#include "Framework/Utils/PrismAsynchronousContext.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class PrismFailoverAgentContext : public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                    PrismFailoverAgentContext (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                    ~PrismFailoverAgentContext ();

                void                setFailedLocationIds(const vector<LocationId> &failedLocationIds);
                vector<LocationId> &getFailedLocationIds      ();

                void                setServiceToBeIgnored     (const WaveServiceId &serviceToBeIgnored);
                WaveServiceId      getServiceToBeIgnored     () const;

                bool                getIsConfigurationChange  () const;
                void                setIsConfigurationChange  (const bool isConfigurationChange);

    // Now the data members

    private :
        vector<LocationId> m_failedLocationIds;
        WaveServiceId     m_serviceToBeIgnored;
        bool               m_isConfigurationChange;

    protected :
    public :
};

}

#endif // PRISMFAILOVERAGENTCONTEXT_H
