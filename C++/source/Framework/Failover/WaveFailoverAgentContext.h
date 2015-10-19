/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFAILOVERAGENTCONTEXT_H
#define WAVEFAILOVERAGENTCONTEXT_H

#include "Framework/Utils/WaveAsynchronousContext.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveFailoverAgentContext : public WaveAsynchronousContext
{
    private :
    protected :
    public :
                                    WaveFailoverAgentContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                    ~WaveFailoverAgentContext ();

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

#endif // WAVEFAILOVERAGENTCONTEXT_H
